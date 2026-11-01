# Historical byte encodings — wave 2

`modules/ClassicEncoding.bui` imports Xojo without importing the RBClassic entry.
The entry must publicly import this module to export `ClassicEncoding` and
`ClassicEncodings`. No selective global functions or new dependencies are needed.
It deliberately does not extend the shipped `TextEncoding.Value` enum or impersonate
`Encodings.MacRoman`: that type cannot truthfully represent these additional tables.

`ClassicEncodings.MacRoman()`, `.ISOLatin2()` and `.DOSLatinUS()` return strict
codecs. `New ClassicEncoding(name)` accepts exactly those case-sensitive names;
unknown encodings raise UnsupportedFormatException. The codecs use complete
256-entry Unicode tables with an exact reverse lookup. No best-fit substitutions,
normalization, locale dependence, encoding guessing, or replacement characters
are applied. DOSLatinUS means code page 437's text mapping; control bytes retain
their control-code meaning rather than DOS display glyphs.

| Method | Contract |
| --- | --- |
| DecodeBytes(raw) | Historical Bytes to UTF-8 Bytes; preserves U+0000 |
| EncodeBytes(utf8) | Strict UTF-8 Bytes to historical Bytes; preserves NUL |
| Decode(raw) | Historical Bytes to String; rejects decoded U+0000 |
| Encode(value) | String's existing UTF-8 content to historical Bytes |

All Bytes-taking methods reject Nil with NilObjectException. Empty input returns
empty output. Malformed UTF-8 (bad leads/tails, truncation, overlong forms,
surrogates, values above U+10FFFF) and unmappable scalars raise EncodingException.
No output is returned on failure, and caller-owned input buffers are not changed.
Decode's NUL rejection is UnsupportedFormatException, directing callers to Bytes.
Encode cannot recover a U+0000 or suffix already lost when another API constructed
a Buoy String: callers handling arbitrary original data must retain Bytes.
Xojo's Nil-encoded String identity and in-place DefineEncoding are not emulated.

## Mapping provenance

The mappings were read from the authoritative published Unicode mapping files:

- [Apple Mac OS Roman c02, 2005-04-05](https://www.unicode.org/Public/MAPPINGS/VENDORS/APPLE/ROMAN.TXT), SHA256 `18e571645be895e9553ed5c842ea8f65f9c5d3c9ccb43e66e0c33a132ed0d721`.
- [ISO 8859-2 table 2.0](https://www.unicode.org/Public/MAPPINGS/ISO8859/8859-2.TXT), SHA256 `020946e114335b17e7d29fe8a8449786cffed714cf409b11d0b3a375197188d1`.
- [Microsoft CP437 table 2.00](https://www.unicode.org/Public/MAPPINGS/VENDORS/MICSFT/PC/CP437.TXT), SHA256 `6bad4dabcdf5940227c7d81fab130dcb18a77850b5d79de28b5dc4e047b0aaac`.

Apple's mapping omits C0/DEL controls; bytes 0..31 and 127 are explicitly mapped
to the corresponding Unicode controls. In particular MacRoman 0xDB is Euro,
0xBD is Greek capital Omega (not Ohm sign), and 0xF0 is U+F8FF. This is the modern
Mac OS Roman mapping, not the pre-Mac OS 8.5 currency-sign variant. Source files
carry Apple/Microsoft/Unicode attribution; Unicode mapping use terms are at
[Unicode terms of use](https://www.unicode.org/copyright.html). Only numeric
mapping data and independently encoded oracle bytes are included here.

## Verification and integration handoff

The source test `tests/classic_encoding_test.bui` contains three full 256-byte
UTF-8 expected-output oracles derived from those mapping files, separate from the
Buoy encoder/decoder implementation. It asserts decode and encode independently
against those fixed expected values, plus representative text fixtures, empty/Nil,
NUL, malformed UTF-8, unsupported codecs and unmappable supplementary text.
This is 768 exact decoding values and 768 exact encoding values. Pure table
roundtrip assertions alone would not detect a mutually incorrect map; the fixed
oracles are therefore required.

The final validation stages copies of both modules, both tests, all scoped repros
and `.buoy/packages` under a fresh `/tmp/classic-wave2-files-*` directory. No shared
package archive or cache is modified. Commands, compiler JSON arrays, source and
compiler hashes, build outcomes and stdout are retained in
`upstream-issues/classic-wave2-encoding/evidence.json`.

Commands from that temporary workspace:

```sh
buoy FILE.bui --target TARGET --check --diagnostic-format json
buoy classic_encoding_test.bui -o classic_encoding_test
buoy classic_files_test.bui -o classic_files_test
LD_LIBRARY_PATH=/usr/lib/buoy/runtime/x86_64-unknown-linux-gnu:/tmp/buoy-chatui-jpeg8/build ./classic_encoding_test
LD_LIBRARY_PATH=/usr/lib/buoy/runtime/x86_64-unknown-linux-gnu:/tmp/buoy-chatui-jpeg8/build ./classic_files_test
```

Targets: x86_64-linux, arm64-linux, x86_64-darwin, arm64-darwin,
x86_64-windows, arm64-windows. All authored `.bui` files must have empty errors;
the inherited XojoDesktop Show warning is advisory. Cross-target semantic checks
are not foreign native execution. Linux behavior tests run from the temporary
workspace and `/` to preserve application-directory path-mode assertions.

Completed roadmap scope: MacRoman plus ISO Latin 2 and DOS CP437 raw-byte codecs;
explicit named FileType registry; real Delete error state on a separate wrapper;
opt-in POSIX symbolic-link resolution; POSIX modification-time setting. Remaining:
Finder alias/Windows shortcut resolution, Windows timestamp setting, creation-time
mutation, SaveInfo/bookmarks, implicit legacy default text encodings and Nil-encoded
String semantics. Parent owns aggregate exports, manifest, roadmap and releases.

## Independent review

Independent review rechecked all 768 mappings and the test oracles against the
primary Unicode files, and reproduced two case-sensitivity contract defects.
The constructor now uses explicit case-sensitive comparisons; regression tests
reject lowercase/uppercase variants. FileType registry comparisons received the
same correction, with distinct-name and exact-replacement assertions. Original
scope evidence predates these fixes and does not certify the revised source hashes.
Parent validation after the fixes passed 24 six-target checks (both modules and
tests) and both Linux behavior suites. Runtime execution used a private Docker
display with current host Buoy runtime libraries mounted read-only, because the
GUI image alone lacked `libbuoy_picture.so` required by the current compiler.

The review also independently reproduced both unpublished native-binding
candidates. CFE-001 is an installed Linux SDK export-coverage gap for ordinary
`remove`/`utimensat` bindings. CFE-002 narrows to allocated-output `realpath`:
ordinary binding fails while a caller buffer and optional binding succeed.
Native symbol-version controls reproduce the old glibc compatibility behavior;
compiler-internal causation remains unproven. Neither candidate has been published
or promoted into the central issue queue. See the scoped evidence directory.

## Unicode data license

Retained from [Unicode license.txt](https://www.unicode.org/license.txt) for the derived mapping tables and test oracles. Apple mapping attribution: Copyright (c) 1994–2002, 2005 Apple Computer, Inc. Microsoft table attribution: Shawn Steele, Microsoft, 1996.

```text
UNICODE LICENSE V3

COPYRIGHT AND PERMISSION NOTICE

Copyright © 1991-2026 Unicode, Inc.

NOTICE TO USER: Carefully read the following legal agreement. BY
DOWNLOADING, INSTALLING, COPYING OR OTHERWISE USING DATA FILES, AND/OR
SOFTWARE, YOU UNEQUIVOCALLY ACCEPT, AND AGREE TO BE BOUND BY, ALL OF THE
TERMS AND CONDITIONS OF THIS AGREEMENT. IF YOU DO NOT AGREE, DO NOT
DOWNLOAD, INSTALL, COPY, DISTRIBUTE OR USE THE DATA FILES OR SOFTWARE.

Permission is hereby granted, free of charge, to any person obtaining a
copy of data files and any associated documentation (the "Data Files") or
software and any associated documentation (the "Software") to deal in the
Data Files or Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, and/or sell
copies of the Data Files or Software, and to permit persons to whom the
Data Files or Software are furnished to do so, provided that either (a)
this copyright and permission notice appear with all copies of the Data
Files or Software, or (b) this copyright and permission notice appear in
associated Documentation.

THE DATA FILES AND SOFTWARE ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF
THIRD PARTY RIGHTS.

IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS NOTICE
BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES,
OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE DATA
FILES OR SOFTWARE.

Except as contained in this notice, the name of a copyright holder shall
not be used in advertising or otherwise to promote the sale, use or other
dealings in these Data Files or Software without prior written
authorization of the copyright holder.
```

## Final resumed validation result

After checkpoint 6b7b8685, all seven authored sources (two modules, two tests,
three candidate repros) were freshly checked on all six targets: **42/42 semantic
checks passed** with empty errors. Both Linux x86_64 behavior executables passed;
the file executable also passed from `/`. Python os.stat verified exact on-disk
mtime **1234567890123000000 ns** with access time unchanged at
**987654321098765432 ns**. The isolated network-disabled Docker/dbus/Xvfb run passed
all **seven** real native cancellation paths, including named FileType filters.
Windows x86_64 and ARM64 file-test cross-links passed. Both macOS cross-links remain
blocked by the local SDK's absent Security/CoreFoundation frameworks and libc++;
the file-scope remove/utimensat missing exports are resolved by the local adapter.
No Windows/macOS runtime result is claimed in this scope.

The source-to-oracle review checked strict UTF-8 validation, exact reverse-table
lookup, NUL policy, integer division and per-instance native error reset. Independent
agent review remains pending because this assignment prohibits spawning agents.
No new upstream record is marked ready and no issue was published.

Distribution handoff: preserve this note's Unicode data license and source mapping
attributions when packaging the codec tables or the derived test oracles. No extra
native payload, package reseal, or cache publication was performed here.
