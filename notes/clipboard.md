# ClassicClipboard native raw interchange — wave 2

`modules/ClassicClipboard.bui` supplies the distinct `ClassicClipboard` wrapper
and `ClassicClipboardFormat(dataType)` function. It imports Xojo directly and
never imports the RBClassic entry. It leaves the shipped Clipboard extensions,
ClassicFiles, RBPasteboard and ClipboardKit unchanged. This is a Bytes-based
migration API: Buoy String cannot preserve arbitrary legacy binary strings or
embedded NUL, so RawData deliberately returns/accepts Bytes rather than pretending
to implement the old String signature.

The parent-owned entry needs a public import of ClassicClipboard for the class
and a selective public import of `ClassicClipboard.{ ClassicClipboardFormat }`
for the global helper, following the entry's existing selective-function pattern.
The test imports Xojo and ClassicClipboard directly. No new package, native bridge,
vendored binary, manifest dependency or install step is needed. All staging and
compiler/native tests use temporary sources and copied installed packages.

## Implemented contract

- `Text`, `TextAvailable()`, `RawData(type)`, `RawData(type) = bytes`,
  `SetRawData(type, bytes)`, `RawDataAvailable(type)`, `Clear()`, `Close()`,
  `Cancel()` and `IsClosed` are available.
- Reads access the live clipboard; staged writes are invisible. SetRawData
  copies Bytes defensively and replaces an already-staged canonical type.
  Multiple representations become one replacement on Close, preserving text
  alongside HTML/RTF/custom bytes. This is one logical clipboard item, not a
  multi-item history or incremental append to another application's selection.
- Close without staged content preserves the owner. Close is idempotent and
  single-use; reads, writes and Clear after Close raise InvalidArgumentException.
  Cancel discards staging and closes without touching the OS. Clear immediately
  clears the OS clipboard, discards staging and leaves the wrapper open.
- Nil bytes and empty names raise InvalidArgumentException. Unsupported formats
  and unsupported empty writes raise UnsupportedOperationException before commit.
  Native Mac allocation, staging, unavailable board and write failures raise
  IOException. The wrapper closes even if Close fails: the native owner might
  already have changed and retry must be deliberate on a new instance. A failed
  write after clearing cannot restore the previous owner. The Windows/Linux
  runtime provides no structured commit error result; this adapter does not
  invent one or claim rollback/strong transaction guarantees.

| Platform | Actual native behavior implemented |
| --- | --- |
| macOS | Literal UTI names are passed directly to NSPasteboardItem, avoiding Buoy's custom MIME-to-private-UTI mapping. Exactly four UTF-8 bytes are assembled as an OSType and converted using UTCreateStringForOSType + UTTypeCreatePreferredIdentifierForTag with com.apple.ostype/public.data. Known and dynamic UTIs use the system registry, not a guessed lookup table. Aliases stage under their canonical type. Bytes use CFData; all representations are staged before clearing, then one writeObjects call publishes the item. Raw reads copy the native NSData and verify changeCount. |
| Windows | Runtime Clipboard SetData/GetData use literal registered native format names. `HTML Format` passes the complete CF_HTML byte stream unchanged; this adapter adds/removes no header. `public.rtf` maps to `Rich Text Format` for native RTF interchange. Other names, including four-byte custom names, remain literal Windows registered formats. Duplicate ASCII case variants replace the staged value. |
| Linux | Runtime GDK providers publish literal MIME targets. `public.rtf` maps to `text/rtf`, `public.html` to `text/html`; other values must be MIME type/subtype tokens without parameters. Case and bytes of literal target names are preserved. The GTK selection owner must remain alive and pump the event loop while other processes retrieve its data. |

Native Mac FFI declarations and staging follow the maintained
`libraries/rbcodec/modules/RBPasteboard.bui`; CoreServices is loaded with documented
dlopen/dlsym APIs because it is outside Buoy's minimal framework link stubs.
ClipboardKit's transaction model guided the staged snapshot/copy behavior, without
adding an import of its extra package or bypassing native UTI semantics.

## Explicit boundaries

Mac implementation is six-target checked, but no macOS native run was performed
this wave. Windows literal formats, RTF mapping and CF_HTML fixture are likewise
compiler-checked only; the parent coordinates final foreign desktop validation.
No foreign ABI, application paste, persistence after process exit or empty-data
support is certified by Linux execution. The supplied Python peer is Linux-only.

On Windows/Linux this wrapper rejects zero-byte raw writes explicitly. Linux's
runtime silently omitted such a target in the independent native probe; the
Windows restriction is conservative, not a measured Win32 failure. Zero-byte raw
reads may be indistinguishable from absent data in the runtime backend. Native
Mac CFData permits empty data, but that path still needs native execution.
Absent ordinary raw data returns Nil. Raw plain-text names are reserved; use Text
instead. No lossy raw String overload is supplied, and existing NUL truncation
before entry to this adapter cannot be recovered. Empty Text remains a distinct
built-in representation, not Clear.

Mac MIME strings, old NSPboardType aliases and synthetic CorePasteboardFlavorType
names are not accepted as UTIs; use a literal UTI or a four-byte MacType. Linux
rejects unmapped UTIs/MacTypes and Windows `HTML Format`; Windows `public.html`
is rejected in favor of a caller-provided complete CF_HTML payload. No broad UTI
registry translation on Windows/Linux, MIME parameter parsing, picture/file
adapters, clipboard-format enumeration, change notifications, delayed rendering,
multi-item boundaries, legacy String encodings or promised/persistent-owner
service is implemented. No named type invents stored-only parity.

## Verification and integration handoff

The final sources and both candidate repros passed 24 real Buoy 0.72.0 compiler
JSON checks: four `.bui` files across x86_64-linux, arm64-linux, x86_64-darwin,
arm64-darwin, x86_64-windows and arm64-windows. All error arrays were empty. The
only advisory warning is the shipped XojoDesktop.Show extension shadowing a
Window member. The three executables built successfully for host x86_64 Linux.

`tests/classic_clipboard_test.bui` independently asserts staging, live baseline
reads, defensive binary copies, replacement of staged RTF, Nil rejection,
explicit zero-byte rejection, Close idempotence, closed-write rejection,
cancellation, empty Close, absent-data Nil, Linux type validation, immediate
Clear and discarded pending text/custom data. `tests/classic_clipboard_verify.py`
is a separate ctypes/GDK/GIO client, with no Buoy clipboard implementation in its
native peer. It checks exact UTF-8 Unicode, HTML, RTF and `00 01 FF 00 42` bytes
from the Buoy writer, then keeps an independent native owner alive while a fresh
Buoy process checks native availability and reads those representations. A third
Buoy process clears, and the native client verifies text/custom targets absent.
GIO reads are asynchronous, so the peer continues to service X11 events.

Stage the module, test and verifier together in a fresh temporary directory;
copy installed `/usr/share/buoy/packages/*.buipkg` into its `packages/` directory.
From that directory run `buoy FILE --check --diagnostic-format json --target TARGET`
for every file/target above, then `buoy classic_clipboard_test.bui -o clipboard-test`.
With that directory mounted read-only as `/work`, execute:

```
python3 /work/classic_clipboard_verify.py /work/clipboard-test
```

Run inside `buoy:0.72.0-gui` with the `/bin/sh` entrypoint, private
`dbus-run-session -- xvfb-run -a`, `/tmp/runtime-buoy` mode 0700, `--network none`,
`--rm`, a unique container name, a 55-second host subprocess timeout and
`docker rm -f` in finally. No Openbox is required: no window state is exercised.
The verifier requires Python ctypes, GTK4/GIO, and stdbuf, all present in that
image. Keep the compiler-produced sibling runtime `.so` files with the executable.
The GUI image supplies its system GTK/JPEG dependencies. No clipboard data leaves
the isolated display/container and no installed toolchain/cache/archive is edited.

Final output: independent reader Unicode/RTF/HTML/binary passed; independent writer,
first-access TextAvailable, raw reads and native Clear verification passed.
Fingerprints, 24 parsed compiler results and native log are preserved under
`upstream-issues/classic-wave2-clipboard/`. CC-001 records initial remote HasText
freshness (worked around locally); CC-002 records zero-byte omission. These are
unindexed candidates with independent review pending, not published/ready issues.

Roadmap scope completed: real raw format access/interchange, literal Mac UTI
backend plus registry-based MacType conversion, Windows registered/custom/HTML
format path, Linux MIME/RTF/HTML interchange, Bytes/NUL preservation for nonempty
raw data, coherent staged multi-format ownership and tested clear/close/cancel.
Entry/manifest/runner integration, roadmap edits, packaging and foreign native
acceptance remain parent-owned.

## Independent review

Independent review repeated all 24 compiler checks and Linux interchange tests,
plus first-access raw reads, changing native owners, defensive input/output
copies and closed-object rejection. No Linux correctness blocker was found.
Both unindexed candidates reproduced: CC-001 is limited to initial asynchronous
format discovery; CC-002 concerns omitted zero-byte publication, while a native
GDK owner can serve empty bytes. Root causes and upstream duplicates remain open.

Foreign acceptance should include case-variant UTI replacement (Apple describes
UTIs as case-insensitive), macOS acquisition/allocation failure cleanup, registry
results and empty data, plus Windows native ownership. The current Mac staging
comparison uses literal case-sensitive UTI strings; that remains an advisory
requiring resolution before broad Mac interoperability acceptance. The Windows
CF_HTML fixture offsets were independently checked as 105/189/137/157; this
does not replace native Windows transport testing.

## Primary references

- [Xojo Clipboard.RawData and RawDataAvailable legacy methods](https://docs.xojo.com/api/user_interface/clipboard.html#clipboard-rawdata): four-byte MacType versus UTI contract, public.rtf and Windows HTML Format. The obsolete `https://docs.xojo.com/Clipboard.RawData` URL was unavailable; this official page retains the exact legacy method documentation.
- [Xojo accessing the clipboard](https://documentation.xojo.com/topics/text_handling/accessing_the_clipboard.html): close-after-write and multi-representation usage.
- [Apple OSType/UTI conversion](https://developer.apple.com/library/archive/documentation/FileManagement/Conceptual/understanding_utis/understand_utis_tasks/understand_utis_tasks.html): UTCreateStringForOSType, preferred identifiers and dynamic types.
- [Microsoft HTML Clipboard Format](https://learn.microsoft.com/en-us/windows/win32/dataxchg/html-clipboard-format): registered name, UTF-8 envelope and byte offsets. The Windows test fixture contains a complete document with byte-accurate fragment offsets, not plain HTML under a misleading native name.
- Installed `/usr/share/buoy/docs/documentation/clipboard.md`: staged-close behavior, live reads and actual backend type mappings.
