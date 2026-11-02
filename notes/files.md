# ClassicFiles implementation notes

## Integration

The entry module needs `Public Import ClassicFiles` and selective public imports of these globals: `GetFolderItem`, `GetOpenFolderItem`, `GetSaveFolderItem`, `GetTemporaryFolderItem`, `SelectFolder`, `RegisterClassicFileType`, `ClearClassicFileTypes`, `ResolveClassicFileTypes`. The plain public import carries the extensions, including their overloads. Do not add duplicate encoding globals. This module imports only the installed Xojo foundation, with no dependencies on sibling Classic modules.

FolderItem and stream source types remain unchanged. Callers wanting legacy Delete/error state explicitly construct `ClassicFolderItem` from a path or an existing FolderItem; GetFolderItem continues to return the foundation FolderItem. Export the new class through the entry module. PathTypeAbsolute/Shell/URL/Native are Shared extension getters with the legacy values 0/1/2/3. They support the old member spelling, but cannot be used where a compile-time constant expression is required. They must not be confused with the foundation's three-value PathModes enum.

## Supported contracts

- `GetFolderItem("")` and no-argument calls return the application directory. On macOS a normal `.app/Contents/MacOS` executable maps to the directory containing the bundle. Relative paths are anchored there, independently of the process working directory. Missing files produce non-Nil references with Exists=False. Native and escaped shell paths and percent-encoded file URLs use the foundation decoder. Shell paths must be absolute; URLs must start with `file:///`. Bad modes, malformed URL escapes, and URL-encoded NUL raise UnsupportedFormatException. On macOS, mode 0 HFS colon paths are explicitly unsupported; use Native/Shell/URL. The shared foundation does not implement Finder alias files or Windows shortcut resolution; neither GetFolderItem nor Item adds it. OS symlink behavior is inherited.
- `GetTemporaryFolderItem` returns the foundation's unique candidate in SpecialFolder.Temporary. It does not create/reserve a file and is not an atomic secure-temp primitive. The foundation uses PID/counter/existence checks; callers must create and clean up their files.
- Open/save/folder dialogs are native and return Nil on cancellation. Save returns a location without creating a file. SelectFolder raises IOException if the native result is not a directory (a failure reproduced on this Linux runtime). Empty String filters allow all files; FileType-object overloads apply real native filters. Nonempty String filters resolve an explicitly registered, semicolon-separated list of FileType names. `RegisterClassicFileType(name, value)` replaces an existing exact, case-sensitive name; empty names, semicolons in names and Nil values are rejected. `ResolveClassicFileTypes` validates the entire list before any dialog opens; unknown names and empty tokens raise UnsupportedFormatException. `ClearClassicFileTypes` releases the application registry. No IDE registry discovery or pipe/glob reinterpretation is claimed.
- `FolderItem.Directory` reads IsFolder. `Item(index)` is one-based; zero/negative/out-of-range indexes and non-directory/missing/unlistable paths return Nil. Listing is refreshed every call, has native order, and cannot distinguish empty directories from unreadable listings. A Nil receiver raises NilObjectException. The base type has no new LastErrorCode; the separate wrapper owns only its Delete result.
- `OpenAsTextFile()` returns a UTF-8 TextInputStream, or Nil for a missing/unopenable path or directory. `CreateTextFile()` creates/truncates UTF-8 text and returns Nil on create failure. Nil receivers raise NilObjectException. These are limited legacy opening equivalents; no system-encoding sniffing, classic file type/creator metadata, or MacRoman default is claimed. Native text streams retain their own LastError behavior.
- Added verified SpecialFolder names: Movies, Music, Pictures. They wrap System.Folders and preserve Nil for unavailable locations; a returned path need not exist. Other existing SpecialFolder names come from XojoFiles.
- `BinaryStream.ReadInt8/ReadUInt8` return sized signed/unsigned values, independent of LittleEndian; EOF returns zero. WriteInt8/WriteUInt8 emit exactly one byte. Inputs use Buoy's native sized-integer conversions (narrowing keeps low bits). Wrapper writes raise IOException when native LastError reports failure; native Bytes operations keep their existing error channel.
- `WritePString(String)` writes one unsigned byte of UTF-8 byte length, then those bytes. The Bytes overload preserves arbitrary bytes, including NUL and invalid UTF-8. Length 0..255 is accepted; larger values raise InvalidArgumentException before writing anything. `ReadPStringBytes()` reads the same framing; missing prefix or incomplete payload returns empty Bytes, consuming any available payload. The native stream LastError remains authoritative, including its EOF/short-read behavior; there is no claim that ReadError exactly matches Xojo.
- `ReadPString(TextEncoding)` and `Read(count, TextEncoding)` explicitly decode using the supplied encoding. Invalid encodings/byte sequences retain EncodingException behavior; negative Read counts raise InvalidArgumentException. No-argument/Nil-encoding PString reads, and Nil-encoding raw String reads, raise UnsupportedFormatException before consuming bytes. Buoy cannot represent Xojo's Nil-encoded binary strings; use Read(count) As Bytes or ReadPStringBytes instead. Decoding a U+0000 code unit also raises UnsupportedFormatException, after consuming the frame/read: the installed core otherwise silently truncates the resulting String. UTF-8, ASCII, Latin1, Windows1252, UTF16/LE/BE, UTF32 and Auto use the foundation encoding model and detection limits.
- `BinaryStream.Write(String)` writes UTF-8 bytes without framing. Existing `Read(count)`/`Write(Bytes)` remain native Bytes APIs; no return-type-only replacement is attempted.

## Remaining compatibility limits

Linux folder confirmation can return a non-directory location; the adapter rejects
that result with IOException. Successful folder confirmation is not guaranteed.
Remaining gaps include Finder aliases/Windows shortcuts, listing error details,
LastErrorCode beyond Delete, HFS and Windows short shell paths, IDE FileType
registry discovery, atomic temporary creation and lossless Nil-encoded Strings.
macOS bundle paths and Windows paths need native validation for each application.

## Native file operations

`ClassicFolderItem Inherits FolderItem` adds synchronous `Delete()`, read-only
`LastErrorCode`, and read-only `NativeErrorCode`. Delete removes a file, final
symbolic link, or empty directory; it never recursively deletes a directory.
The result state is per wrapper, starts at zero, and resets before every Delete.
It does not claim to track foundation Rename/Copy/Move/Remove operations.
A missing path maps to legacy FileNotFound=101; access denial, memory exhaustion,
busy/sharing, and invalid names map to 102/103/104/105 for the enumerated native
errors in source. Unmapped failures retain their native value. NativeErrorCode
always preserves the actual errno/GetLastError (zero on success); on macOS this
is POSIX errno rather than an invented Carbon error. These mappings follow the
[archived LastErrorCode contract](https://documentation.xojo.com/versions/2022r4/api/deprecated/deprecated_class_members/folderitem.lasterrorcode.html).

POSIX Delete uses libc remove. Windows uses strict UTF-8 to UTF-16 conversion,
DeleteFileW, GetFileAttributesW and RemoveDirectoryW; it does not depend on the
foundation's narrow-path IsFolder query for Unicode directory deletion. Long
Windows paths still require OS-supported extended-path syntax/policy. Validate Windows native operations on the target host.

`FolderItem.ResolveSymbolicLinks()` uses public POSIX realpath, resolves dot
components and complete existing symbolic-link chains, copies the returned UTF-8
path before freeing it, and throws IOException with errno for missing/broken/looping
paths. This is opt-in; GetFolderItem and Item keep their prior resolution behavior.
It does not read Finder alias files, Windows .lnk files, or security-scoped bookmarks.
Windows calls explicitly raise UnsupportedFormatException.

`FolderItem.SetModificationDateTime(instant)` uses public POSIX utimensat with
UTIME_OMIT for access time and DateTime's millisecond timestamp. Negative timestamps
use floor decomposition. It follows final symlinks, matching normal timestamp
updates. Missing paths raise IOException with native errno. Windows explicitly
raises UnsupportedFormatException. Creation-time mutation, legacy Date setters,
and SaveInfo/bookmark serialization remain unsupported; no stored-only timestamps
or path strings masquerade as relocatable bookmarks. The shipped modification-time
getter reads whole seconds, even when the setter preserves milliseconds on disk.

No new package/native payload is required: this module imports only Xojo and uses
public libc/Win32 functions. Linux remove/realpath/utimensat use Optional Declare to
resolve the actual host libc at runtime, avoiding the installed ordinary-declaration
link/runtime gaps captured in the runtime compatibility boundary. macOS resolves remove/utimensat with public dlsym, following the maintained
FileSystemKit approach, to avoid absent linker exports without modifying toolchain
stubs. Other libc calls retain the existing runtime binding. Missing optional symbols throw the
standard LibraryUnavailableException, rather than silently succeeding.

## Primary references

- [Archived GetFolderItem: empty path and legacy mode values](https://documentation.xojo.com/versions/2022r4/api/deprecated/getfolderitem.html)
- [Archived FolderItem.Item: one-based index, Nil and alias behavior](https://documentation.xojo.com/versions/2022r3/api/deprecated/deprecated_class_members/folderitem.item.html)
- [Archived Directory alias](https://documentation.xojo.com/versions/2022r3/api/deprecated/deprecated_class_members/folderitem.directory.html)
- [Archived open dialog filters/cancellation](https://documentation.xojo.com/versions/2022r4/api/deprecated/getopenfolderitem.html), [save location behavior](https://documentation.xojo.com/versions/2022r4/api/deprecated/getsavefolderitem.html), [SelectFolder](https://documentation.xojo.com/versions/2022r4/api/deprecated/selectfolder.html), [temporary location](https://documentation.xojo.com/versions/2022r4/api/deprecated/gettemporaryfolderitem.html)
- [Archived BinaryStream: byte signedness, EOF returns and PStrings](https://documentation.xojo.com/versions/2022r4/api/files/binarystream.html), [SpecialFolder names](https://documentation.xojo.com/versions/2022r4/api/files/specialfolder.html)
- Local `/usr/share/buoy/docs/documentation/`: extension-methods.md, sized-integers.md, bytes.md, binarystream.md, filesystem-item.md, application-executable.md, file-dialogs.md, filetype.md, special-folders.md, textinputstream.md, textoutputstream.md, text-encoding.md, command-line-args.md; installed XojoFiles.bui and XojoText.bui.
