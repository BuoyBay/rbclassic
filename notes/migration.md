# Classic migration diagnostic CLI — implementation notes

The migration diagnostic scans UTF-8
legacy RB text sources without modifying them. Use `-` for stdin and
`--format json` for tooling. There is no rewrite option. Python 3.10+ and its
standard library are sufficient; the linter does not import compatibility
modules or require Buoy to be installed.

Exit status is 0 below the requested threshold, 1 for findings at/above the
threshold, and 2 for input/argument errors. The default threshold is `warning`;
`--fail-on never` suppresses finding-driven failure, including lexical findings,
but never input/argument errors. Both readable output and JSON report source
locations, severity, stable `CXnnn` codes and remediation. JSON schema version 1
has `files`, `diagnostics`, and `input_errors` arrays. Findings carry a
`heuristic` Boolean. Locations use one-based physical lines and Unicode code
point columns; a tab counts as one column. CRLF, LF, and CR are recognized.
`CX003` input errors use line/column 1 because no usable source position exists.
Argparse usage errors go to stderr rather than producing JSON.

Directory scans recognize `.rbbas`, `.rbclass`, `.rbmodule`, `.rbfrm`, `.rbcode`,
`.xojo_code`, `.xojo_window`, `.xojo_menu`, `.xojo_script`, and `.xojoscript`
(case-insensitively). They skip hidden directories, directory/file symlinks,
and other extensions. Explicit file paths accept any extension, including
an explicitly requested symlink. Repeated resolved file paths are deduplicated.
An empty scan reports zero files; it is not a project-coverage assertion.
Export binary/XML projects to text source first. UTF-8 BOMs are accepted;
invalid UTF-8 and NUL bytes fail explicitly. No encoding guessing occurs.

## Stable rule inventory

| Code | Severity | Meaning |
| --- | --- | --- |
| CX001 | error | Unterminated source string |
| CX002 | error | Unterminated block comment |
| CX003 | error | Unreadable, undecodable or unsupported NUL-containing input |
| CX101 | error | `&` / `&=` concatenation |
| CX102 | warning, heuristic | `/` numeric promotion/truncation review |
| CX103 | error | legacy doubled-quote string escape |
| CX104 | error | `Module` / `End Module` block |
| CX105 | error | `Soft Declare` |
| CX106 | error | `Raise` statement |
| CX201 | warning, heuristic | Three-argument `New Picture` depth-versus-scale trap |
| CX202 | warning, heuristic | `Color.RGB` / `RGBA` byte channels and transparency-versus-opacity |
| CX203 | warning | `Catch ... As RuntimeException` is not Buoy's catch-all |
| CX204 | warning, heuristic | First-only `Replace` versus all replacements and empty-search behavior |
| CX205 | error | `ReDim` upper bounds versus Buoy lengths |
| CX206 | warning | Bounded `Dim`/`Var`/`Property` arrays use inclusive source upper bounds |
| CX301 | warning, heuristic | API1 index origin, sentinel, byte-unit, dimension and resize transitions |
| CX302 | warning, heuristic | Possible API1 event declaration/handler transition |
| CX303 | warning, heuristic | Native type collision requiring a Classic wrapper type rewrite |
| CX401 | warning, heuristic | Stream data, encoding, EOF and error-state contract |
| CX402 | warning, heuristic | Database SQL/RecordSet and stored-error contract |
| CX403 | warning, heuristic | Boolean API1 `Connect` versus exception-throwing API2 `Sub Connect` |

## Practical migration targets

Import `rbclassic` for the maintained foundation and adapters chosen
by the package integration. Rewrite source type declarations, constructors,
and superclass names deliberately: `Window` → `ClassicWindow`, `ListBox` →
`ClassicListBox`, `CheckBox` → `ClassicCheckBox`. Native types already own those
original names, so importing extensions cannot select the legacy class.
Use the Classic wrapper's API1 members and exact event signatures. A method
named `Action` or `Open` is not automatically a Buoy event handler; handler
bodies require `Handle` and the event's parameter/return types.

For opaque RGB byte inputs, `Color.FromBytes` is available in native Buoy.
For historical alpha, divide channels by `255.0` and use opacity
`1.0 - alpha / 255.0`; do not infer alpha provenance from a variable name.
Three-argument pictures need a depth/mask-aware adapter or explicit supported
conversion, because the native third argument is scale. First-only string
replacement needs a count of 1 and an empty-search guard (classic returns the
original string; native replacement rejects an empty target).

Use Classic file/stream adapters for classic failure and data contracts;
inspect each supported overload. In particular the bundled one-argument
`BinaryStream.Read` returns `Bytes`, and the encoding overload returns a
`String`. API1 database callers need a Classic database adapter such as
`ClassicSQLiteDatabase` with its `RecordSet`/error-state contract, or a complete
migration of both calls and error handling to API2. Merely renaming `SQLSelect`
to `SelectSQL` cannot preserve Boolean `Connect` and stored error flags.
These are migration destinations, not assertions that every feature of each
adapter is implemented; package/module notes define the supported release.

## Lexical guarantees and limits

Apostrophe, `//`, `/* ... */`, and statement-leading `Rem` comments are excluded
from API matching. Strings use **legacy source** doubled quotes; backslash is an
ordinary source character. String contents never trigger API rules; the quote
escape itself can produce CX103. Ampersand-prefixed numeric/color literals
are excluded from concatenation diagnostics. Nested argument parentheses,
commas inside strings, explicit `_` continuation, and multiline parenthesized
calls are handled. Rules match complete tokens case-insensitively.

This is migration triage, not a legacy RB parser or a Buoy type checker. It does not
resolve scopes, aliases, receivers, overloads, inherited events, constants or
conditional compilation. All conditional source branches are scanned. A user
method called `Replace`, an unrelated `.Connect`, or already normalized
`Color.RGB` may be a heuristic false positive. Classic array declarations and
catch-root warnings assume the supplied input is classic source. Arbitrary
invalid syntax, unusual declaration syntax, escaped identifiers, unparenthesized
calls and project metadata are not fully analyzed; absence of findings does
not establish compatibility. Backslashes in source strings also need manual
conversion even when no doubled quotes occur. Strings are not rewritten.
There is no claim to validate GUI behavior, arbitrary event signatures, native
bindings or database backend availability.
