# RBClassic API 1 adapters

RBClassic helps port legacy RB desktop code to Buoy. It adds
classic member names and checked behavior over the installed compatibility
foundation, existing native controls, and ProcessKit. It is a supported subset with
explicit source rewrites, rather than a drop-in implementation of the entire
historical framework.

Use `Import rbclassic` after placing the sealed package and its dependencies
in the consumer's `packages/` directory. The entry module re-exports the installed compatibility foundation's types and extensions. Legacy global routines are forwarded explicitly, including numeric, encoding, JSON, desktop and scheduling helpers; no second framework import is needed.

## Build

Use the [devtools RBClassic builder](https://github.com/BuoyBay/devtools/blob/main/tools/build_rbclassic.py)
from the assembled [BuoyBay workspace](https://github.com/BuoyBay/workspace-tools).
It stages ProcessKit and the installed foundation dependencies, including
`serialio` for serial I/O and `pdf` for printing. Set `BUOY` for the compiler and
`BUOY_PACKAGES_DIR` for an alternate installed-package directory.

The builder compiles the networking helper for its Linux/macOS host. Other POSIX
targets require a matching native build; Windows networking and TLS are
unsupported. See the [networking contract](../notes/networking.md) and
[ProcessKit target requirements](../notes/processkit-slices.md).

## Supported areas

| Area | Adapter surface | Contract details |
| --- | --- | --- |
| Core routines | `Len`, `Mid`, `InStr`, `UBound`, inclusive-bound `ClassicRedim`, first-only `ClassicReplace`, locale-aware `ClassicFormat` | [Core notes](../notes/core.md) |
| Controls | Classic ListBox, PopupMenu, ComboBox, CheckBox; selection, row/cell tags, sorting, classic events | [Controls](../notes/controls.md) |
| Desktop integration | ClassicWindow events and veto sequence, default/cancel buttons, native text selection/editing, containers and control drops | [Desktop](../notes/desktop.md) |
| Graphics | Classic drawing state, depth-aware pictures, byte colors, drawing/cropping, picture pixels, Canvas mouse capture | [Graphics](../notes/graphics.md) |
| Files | Classic path/dialog helpers, one-based children, limited text opening, byte/Pascal-string stream helpers | [Files](../notes/files.md) |
| Data and dates | Dictionary aliases, checked Variant accessors, mutable ClassicDate | [Data](../notes/data.md) |
| SQLite | Boolean connect/error state, buffered records, reusable statements, binary data, metadata and explicit primary-key editing | [Database](../notes/database.md), [Statements](../notes/statements.md) |
| Serial | Legacy configuration ordinals, Boolean Open/errors, buffered binary reads, lookahead and output-line controls | [Serial](../notes/serial.md) |
| Historical encodings | Strict MacRoman, ISO Latin 2 and CP437 codecs with NUL-safe Bytes methods | [Encodings](../notes/encoding.md) |
| Async networking | DNS/TCP clients and partial classic HTTP/1.0 over a native POSIX helper | [Networking](../notes/networking.md) |
| Clipboard | Staged native raw formats, Bytes/NUL preservation, Close/Clear/Cancel | [Clipboard](../notes/clipboard.md) |
| Control sets | Indexed members/events, cloning, native removal and Linux reparenting | [Control sets](../notes/controlsets.md) |
| Printing | Vector PDF pages, device coordinates, pagination and Linux CUPS/GTK destinations | [Printing](../notes/printing.md) |
| System | Timer modes, per-command shell modes/events, UDP options and binding, symbol lookup, limited POSIX logging | [System](../notes/system.md) |

## Source rewrites

Native Buoy types already own several legacy names. Change source declarations,
constructors and superclass names explicitly:

| Legacy source type or routine | Adapter |
| --- | --- |
| `ListBox`, `PopupMenu`, `ComboBox`, `CheckBox` | `ClassicListBox`, `ClassicPopupMenu`, `ClassicComboBox`, `ClassicCheckBox` |
| `Window`, `ContainerControl`, default/cancel `PushButton` | `ClassicWindow`, `ClassicContainerControl`, `ClassicPushButton` |
| `Quit` when windows must be able to veto closing | `ClassicQuit` |
| `Picture`, `Graphics`, `Canvas` | `ClassicPicture`, `ClassicGraphics`, `ClassicCanvas` |
| `RGB`, `HSV`, `CMY` | `ClassicRGB`, `ClassicHSV`, `ClassicCMY` |
| `Date` | `ClassicDate` |
| API 1 `SQLiteDatabase`, `DatabaseRecord` | `ClassicSQLiteDatabase`, `ClassicDatabaseRecord` |
| `Shell`, UDP with legacy `Port`/`Connect` | `ClassicShell`, `ClassicUDPSocket` |
| Timer needing observed one-shot completion | `ClassicTimer` |

Indexed members and events need their module-specific rewrites too. For example,
ListBox `CompareRows` uses a `ClassicCompareResult` object instead of a ByRef
event result, and array row insertion uses `AddRowItems`. Shared timer constants
use `Timer.ModeSingle`, not an instance qualifier. Read the linked contracts
before changing names mechanically.

This read-only diagnostic CLI flags depth/scale, color, bounds, exception,
replacement, indexing and event traps. It excludes comments and string contents
from API matching and labels rules that cannot resolve receiver types. It does
not translate projects or prove compatibility. See [migration notes](../notes/migration.md).

## Platform and compatibility boundaries

Compiler checks cover x86_64/arm64 Linux, macOS and Windows. Most adapter runtime
coverage is Linux; individual module notes describe narrower native limits.
Shell programs require a ProcessKit native payload matching its maintained
source. Build and exercise each intended host: semantic checks alone do not
establish native linking or behavior.

Unsupported behavior is documented per module and generally omitted or rejected.
Particularly important limits include foreign native ListBox bridges and
hierarchical/editable cells; synchronous Canvas refresh and foreign font metrics;
arbitrary SELECT editing and composite identities; full implicit Variant
conversion; and exact historical encoding/timezone semantics. Database Bytes
preserve binary/NUL values; legacy binary Strings remain unavailable.
Some adapter policies are deliberately stricter than the old framework; they
are identified in the module contracts rather than presented as measured parity.

Foreign printer Graphics, cooperative threads, legacy Serial hardware
status, Windows asynchronous transport/TLS, and complete control-set lifecycle
remain separate runtime projects. See [remaining work](../ROADMAP.md).

## Upstream reports

Wave 2 adds twelve scoped observations with independent reproduction/challenge,
including explicit enhancement and contract-uncertainty dispositions. See the
[wave 2 upstream handoff](../notes/upstream-wave2.md). They remain unpublished and
unpromoted; existing numbered reports below belong to the first wave.

Five defects found during this work have minimal reproductions, independent
reproduction/challenge and validated local reports. They have not been posted:

- Optional Declare aliases with different signatures
- Int32 Math.Min/Max code generation
- Missing Windows user32 import entries
- Bundled RBClassic fixed-size ListBox rows
- Catch/rethrow skipping Finally

The plain GTK Declare lookup observation remains
search-rule/enhancement triage,
not a confirmed compiler defect. Existing BUI-104 tracks early GTK run-loop
termination; the issue handoff retains a smaller supplemental trigger without
creating a duplicate.

[Explicit dynamic-value transport](../notes/dynamic-values.md) documents
`TryToVariant`, `BoxClassicValue` and `TryUnboxClassicValue`, alongside the
opt-in VariantKit exact-key dictionary adapter.

## Names, aliases and the external dependency

The maintained package is **RBClassic**, imported with `Import rbclassic`.
`RBCodec` owns project import/export; this package supplies runtime adapters.
The toolchain's immutable vendor package is still named `Xojo`; only
[RBFoundation](../modules/RBFoundation.bui) imports it. It must be shipped as a
dependency under its actual installed name. Renaming our package cannot rename
that external dependency or the historical file formats.

Use `Lowercase(text)` and `Uppercase(text)` for readable free functions. They
forward to Buoy's `String.LCase` and `String.UCase` with exactly the same casing
contract. `ShowMessageBox(text)` and `KeyNameForMacKeyCode(code)` expose neutral names for
the installed dialog and key-code forwarding routines. Original vendor-prefixed
exports remain available only for source compatibility. Existing `text.Lowercase()` / `text.Uppercase()` receiver helpers also
remain available. `Replace(text, target, replacement)` preserves the classic
first-only replacement contract, while native `String.Replace` defaults to all
occurrences. `ArrayExtent(upperBound)` checks inclusive legacy array bounds.

The [adapter mapping](../resources/buoy-docs/legacy-api-map.md) and
[foundation mapping](../resources/buoy-docs/foundation-api-map.md) inventory every
declared public type, member and global in the supported surface. The complete
[machine-readable map](../notes/legacy-api-map.json) records source modules,
signatures and direct native calls. Keep the maps consistent with API changes.

Buoy has no general source type-alias declaration. Native names such as
`Window`, `ListBox`, `Picture`, `Timer`, `Shell` and `SQLiteDatabase` cannot be
silently replaced with different compatibility behavior. Use the explicit
`Classic*` types in the source-rewrite table. These are real implementations,
not placeholders. Unsupported historical areas remain documented as unsupported.

Builder context: run shared `tools/` commands from the assembled
[BuoyBay workspace](https://github.com/BuoyBay/workspace-tools). The scripts live
in [devtools](https://github.com/BuoyBay/devtools), alongside the shared build inputs.
