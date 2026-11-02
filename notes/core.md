# Classic core routines

`ClassicCore.bui` adds ordinary globals `Len`, `Mid`, `InStr`, `ClassicExtent`,
`ClassicReplace` and `ClassicFormat`, re-exported selectively by `RBClassic`.
`UBound` and `ClassicRedim` are generic extensions, so they also support receiver
syntax and flow through the entry module's public import.

`Mid` uses a one-based character position. `InStr` returns a one-based position
or zero and supports the classic start-first overload. String characters are
Buoy Unicode codepoints; native search uses ASCII case folding. These functions
do not recreate byte strings, grapheme indexing or historical encoding metadata.

`UBound` covers one-dimensional arrays. `ClassicExtent` maps inclusive bounds
to lengths, accepts -1 for empty, and rejects smaller values and signed overflow.
`ClassicRedim` preserves elements while resizing a native resizable array; fixed
arrays retain the runtime's mutation restrictions. Multidimensional declarations
and dimension numbering still require explicit source conversion.

`ClassicReplace` changes the first case-insensitive match and leaves empty
targets unchanged. Its distinct name avoids the native replace-all collision.
`ClassicFormat` uses the installed Xojo numeric-mask implementation with the
current locale, or an explicitly supplied non-Nil locale. It retains that
implementation's mask subset and exceptions. It does not replace the existing
invariant `Xojo.Format`, or claim to fix `CStr`'s precision and locale behavior.
