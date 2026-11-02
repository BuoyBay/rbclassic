# ClassicClipboard native raw interchange

`modules/ClassicClipboard.bui` supplies the distinct `ClassicClipboard` wrapper
and `ClassicClipboardFormat(dataType)` function. It imports Xojo directly and
never imports the RBClassic entry. It leaves the shipped Clipboard extensions,
ClassicFiles, RBPasteboard and ClipboardKit unchanged. This is a Bytes-based
migration API: Buoy String cannot preserve arbitrary legacy binary strings or
embedded NUL, so RawData deliberately returns/accepts Bytes rather than pretending
to implement the old String signature.

The entry module needs a public import of ClassicClipboard for the class
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
compiler-checked only; native macOS and Windows behavior requires validation.
No foreign ABI, application paste, persistence after process exit or empty-data
support is certified by Linux execution.

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

## Primary references

- [Xojo Clipboard.RawData and RawDataAvailable legacy methods](https://docs.xojo.com/api/user_interface/clipboard.html#clipboard-rawdata): four-byte MacType versus UTI contract, public.rtf and Windows HTML Format. The obsolete `https://docs.xojo.com/Clipboard.RawData` URL was unavailable; this official page retains the exact legacy method documentation.
- [Xojo accessing the clipboard](https://documentation.xojo.com/topics/text_handling/accessing_the_clipboard.html): close-after-write and multi-representation usage.
- [Apple OSType/UTI conversion](https://developer.apple.com/library/archive/documentation/FileManagement/Conceptual/understanding_utis/understand_utis_tasks/understand_utis_tasks.html): UTCreateStringForOSType, preferred identifiers and dynamic types.
- [Microsoft HTML Clipboard Format](https://learn.microsoft.com/en-us/windows/win32/dataxchg/html-clipboard-format): registered name, UTF-8 envelope and byte offsets. The Windows test fixture contains a complete document with byte-accurate fragment offsets, not plain HTML under a misleading native name.
- Installed `/usr/share/buoy/docs/documentation/clipboard.md`: staged-close behavior, live reads and actual backend type mappings.
