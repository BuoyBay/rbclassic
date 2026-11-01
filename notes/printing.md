# ClassicPrinting implementation notes

Owned files:

- `modules/ClassicPrinting.bui`
- `tests/classic_printing_test.bui` and `tests/classic_printing_verify.py`, at the repo root
- this note
- `upstream-issues/classic-wave2-printing/`

ClassicPrinting draws pages as vector PDF through the bundled `pdf` package. A finished document goes to one of three destinations: an in-memory PDF, a CUPS queue (Linux), or a GTK 4 printer chosen in the native print dialog (Linux). The module never reports PDF output as a physical print job.

## Integration

The module imports `PDF` (the bundled `pdf-2.4.6.buipkg`) and the sibling `ClassicGraphics` module, which supplies the `ClassicPicture` overloads. It does not import `rbclassic` or `printing`.

```
Public Import ClassicPrinting
Public Import ClassicPrinting.{ OpenPrinter, OpenPrinterDialog, ClassicOpenPDFPrinter }
```

Exported types:

- classes `ClassicPrinterSetup` and `ClassicPrinterGraphics`
- enum `ClassicPrintDestination`, with members `PDF`, `CupsQueue` and `GtkPrinter`

The only public functions are the three named above.

Dependencies:

- **Package.** `pdf` 2.4.6 ships `libpdf` for all six targets. Every program that imports the module therefore links `libpdf`. That is the parent's decision for the `RBClassic` entry.
- **Native libraries.** None are added at build time. Linux libraries are loaded at run time through `Optional Declare`:
  - `libcups.so.2`
  - `libgtk-4.so.1`
  - `libgobject-2.0.so.0`
  - `libglib-2.0.so.0`
  - libc
- **Missing libraries.** A missing library raises `LibraryUnavailableException` only when that path is used. PDF jobs need none of them.
- **Source and payload.** The module is source-only, with no owned native payload.
- **Exported libpdf symbols.** The module also binds symbols from `Lib "pdf"` (see CW2-PRINT-001 below). These are pinned to the pdf 2.4.6 shim names, so a pdf package upgrade must rerun the verifier.

## Source rewrites

| API 1 | Rewrite |
|---|---|
| `Dim p As New PrinterSetup` | `Dim p As New ClassicPrinterSetup` |
| `Dim g As Graphics = OpenPrinter(p)` / `OpenPrinterDialog(p[, w])` | `Dim g As ClassicPrinterGraphics = …` (same calls) |
| `p.ShowPrinterDialog` / `p.PageSetupDialog` / `ShowPageSetupDialog` | same names on `ClassicPrinterSetup` |
| `g.NextPage` | `g.NextPage()` |
| job sent when `g` leaves scope | still happens (destructor). Call `g.ClassicFinishPrinting()` to see errors. |
| `DrawPolygon(points())` | 1-based `Array Of Integer`/`Double`; element 0 is ignored |

The class is named `ClassicPrinterSetup` so that it cannot collide with the separate `printing` package's macOS `PrinterSetup`.

## Supported behavior

**Setup model.** Defaults are US Letter, portrait, 18-point margins and 72 dpi. These are Buoy defaults, not values read from a driver.

- **Device-unit properties.** `PageWidth`/`PageHeight`, `Width`/`Height` (printable area), `Left`/`Top` (always 0), and `PageLeft`/`PageTop` (negative margins) are all in device units at `HorizontalResolution`/`VerticalResolution`, following the Xojo PrinterSetup reference.
- **Resolution requests.** `MaxHorizontalResolution`/`MaxVerticalResolution` (1–9600) are granted exactly, because the output is vector PDF. Read the actual value back as Xojo documents. The legacy API 1 page defines `-1` as "the highest possible resolution of the output device", with `HorizontalResolution` resolved from the printer driver when a dialog or printer is opened. No backend here reports a driver resolution, so `-1` raises `UnsupportedOperationException` instead of being mapped to an invented value. Sources: [MaxHorizontalResolution](https://documentation.xojo.com/api/deprecated/deprecated_class_members/printersetup.maxhorizontalresolution.html) and [PrinterSetup](https://documentation.xojo.com/api/printing/printersetup.html).
- **Paper and margins.** `ClassicSetPaperSize` and `ClassicSetMargins` take points. Margins are relative to the oriented page. Every setter, including `Landscape`, validates the oriented printable area first and rejects a change that would leave none, without modifying anything. For example, portrait margins 0/380/0/400 on Letter cannot switch to landscape. A job also refuses a setup whose printable area rounds to 0 device units.
- **`SetupString`/`Settings`.** This is versioned Buoy JSON with these fields:
  - paper size
  - orientation
  - margins
  - resolutions
  - GTK paper name
  - printer name

  It is not Xojo's driver blob. Invalid input raises before any field changes.
- **`ClassicPrinterName`** selects a CUPS queue for `OpenPrinter`, or preselects a printer in the dialog.

**Printer graphics.** The origin is the printable origin and one unit is 1/resolution inch.

- **API 1 ambient state.** `ForeColor`, `PenWidth`/`PenHeight`, `TextFont`, `TextSize`, `Bold`, `Italic`, `Underline` and `Transparency` are all available.
- **Text size.** `TextSize` is in points at any resolution.
- **Shapes.**
  - `DrawLine`, `DrawRect`/`FillRect`, `DrawOval`/`FillOval`, `DrawRoundRect`/`FillRoundRect` and `DrawPolygon`/`FillPolygon` are supported.
  - Fills cover exactly w×h. They do not follow the shim's raster w+1 rule.
  - **Pen hang.** `DrawLine` fills the convex sweep of the p×p pen square from (x1, y1) to (x2, y2), following the API 1 convention that the pen hangs right/below. With pen 8, a horizontal 100→200 line covers 100..208, and a zero-length line is a p×p dot. `DrawPolygon` sweeps the pen along every closed edge the same way.
  - `DrawRect`/`DrawOval`/`DrawRoundRect` outlines lie inside the bounds. When the pen is at least the width or height, the shape is filled instead.
  - Coordinates, sizes, arcs, polygon points and picture positions must be finite, within ±1e9; NaN or infinity raises `InvalidArgumentException`.
  - The round-rect arc is a radius, matching ClassicGraphics.
- **`DrawString(text, x, y)`** draws one line with `y` as the baseline. Glyphs are laid out in points: a Save/Translate/Scale undoes the device-unit scale at the baseline origin, so text is undistorted even when the two resolutions differ.
- **Text size.** `TextSize` is in points (0 = 12). The limit is libharu's 600-point font size; larger values raise. 1200 dpi/48 pt, 600 dpi/73 pt, 9600 dpi/12 pt and 300×150 dpi/48 pt are all tested.
- **`StringWidth`** converts the PDF font metric width (points) to device units. The test checks it against the Helvetica AFM widths.
- **Fonts.** `System`/`SmallSystem`/`Arial`/`Helvetica`, `Times`/`Times New Roman` and `Courier`/`Courier New` map to the Base14 regular/bold/italic variants. `ClassicLoadFont` embeds a TrueType font.
- **`DrawPicture`.**
  - The 3-argument form draws at natural size, with 1 pixel = 1 device unit.
  - The 5-argument form crops to the top-left destW×destH region, as in API 1.
  - The 9-argument form scales the source rectangle into the destination.
  - Each form accepts a `Picture` or a `ClassicPicture`. Per-pixel alpha is preserved.
- **Pagination.** `NextPage()` starts a new page, up to 10000 pages. `ClassicPageCount` reports the count.

**Job metadata.**

- **`Copies`** is always 1. GTK jobs pass the dialog's copies, collate and reverse settings to `GtkPrintJob`, which matches Xojo's note that macOS handles copies.
- **`FirstPage`/`LastPage`** come from the dialog ranges: the smallest start and the largest end, in any range order. They are 1 and 0 otherwise, and 0 means "all". Pages are submitted as drawn, so applying the range is the application's job.
- **`PrintingCancelled`** reports whether the job was cancelled.

**Lifecycle.**

- **`ClassicFinishPrinting()`.** Exactly one call is valid.
  - For PDF jobs it makes `ClassicPDFBytes()` available.
  - For CUPS it streams the PDF through `cupsCreateJob`/`cupsStartDocument`/`cupsWriteRequestData`/`cupsFinishDocument` with `document-format=application/pdf`. If a later step fails it calls `cupsCancelJob2`, and `ClassicJobId` holds the server's job ID on success.
  - For GTK it writes a private `mkstemp` spool file, runs `GtkPrintJob` `set_source_file` and `send` in a nested main loop, then unlinks the file.
  - Errors raise and leave the job failed. A failed job is never retried or reported as printed.
- **`ClassicCancelPrinting()`** discards every page.
- **Destructor.** If neither call was made, the destructor submits printer jobs, which is Xojo's scope-exit behavior, and swallows any errors. It discards PDF jobs.

**Entry points.**

- **`ClassicOpenPDFPrinter([setup])`** works on all platforms and contacts no print system.
- **`OpenPrinter([setup])`** is Linux only. It targets the named queue, or the CUPS default.
  - It returns Nil when CUPS reports no such or no default queue; client-error-not-found counts as an empty server.
  - It raises `IOException` when CUPS cannot be reached.
- **`OpenPrinterDialog([setup[, window]])`** is Linux only and runs a modal GtkPrintUnixDialog.
  - Cancel or close returns Nil and leaves the setup unchanged.
  - OK copies the dialog's paper, orientation and margins into `setup`. A printer that does not accept PDF raises.
- **`PageSetupDialog`** runs a modal GtkPageSetupUnixDialog: False on cancel, True on accept.
- **Dialog rules.**
  - A window must already be shown, because GTK has to be initialized.
  - The call must run on the main thread.
  - Only one dialog or job can be active at a time.

## Explicit limitations (raise instead of approximating)

- **macOS and Windows.** `OpenPrinter`, `OpenPrinterDialog` and `PageSetupDialog` raise `UnsupportedOperationException`. There is no physical printing there in this wave.
  - A macOS CUPS or `NSPrintOperation` route was not added. An untestable plain macOS `Declare` could break linking for every RBClassic consumer.
  - Windows GDI printing (`PrintDlgEx`/`StartDoc`) is roadmap work.
- **Translucency.** A translucent `ForeColor`, or any nonzero `Transparency` for shapes, text or pictures, raises. The PDF backend writes no alpha for solid paint.
- **Text content.** Text must be printable ASCII. libharu's single-byte encoding would otherwise emit wrong glyphs. Line breaks and tabs raise too.
- **Text layout and fonts.**
  - A `wrapWidth`/`condense` value raises.
  - A `TextSize` above 600 points raises.
  - An unknown font raises instead of falling back silently to Helvetica.
  - Bold or italic on Symbol, ZapfDingbats or a loaded font raises, because those styles are not synthesized.
- **`-1` resolution requests** raise (see Supported behavior).
- **Pens and corners.** `PenWidth <> PenHeight` raises, and so do elliptical corners. Negative sizes, a polygon with fewer than three points, and a non-positive pen also raise.
- **Reverse orientation.** GTK reverse portrait/landscape raises when it is read back.
- **Not provided:** `TextHeight`/`TextAscent`, `Clip`, `ClearRect`/`Pixel`, `DrawObject`, `ScaleX`/`ScaleY`, `Graphics.Copies` handling for non-GTK destinations, sheet-attached macOS dialogs, page-range or printer-specific options in `SetupString`, and a printer list API.
- **NUL in strings (BUI-003).** A Buoy String drops NUL before it reaches the validators, so the NUL guards are defensive only.

**GTK margin model.** `GtkPageSetup` stores margins against the portrait paper edges; the reviewer's native probe shows a landscape page width of paper height − top − bottom. ClassicPrinting rotates at the GTK boundary in both directions, treating landscape as content rotated 90° counter-clockwise (IPP `orientation-requested` 4): oriented left/top/right/bottom are the portrait bottom/left/top/right. Every value read back is cross-checked against GTK's own `gtk_page_setup_get_page_width`/`_height`, and a mismatch raises `IOException`. Four distinct landscape margins (10/20/30/40) round-trip through the real print dialog. That cross-check proves the axis pairing. The order within a pair, such as top versus bottom, follows the IPP definition and was not observed on paper.

**Observed GTK 4.14.5 behavior, not a Buoy defect.** `gtk_page_setup_unix_dialog_set_page_setup` ignores orientation: `get_page_setup` returns portrait immediately after a landscape setup is applied. The page setup dialog therefore opens in portrait, and accepting returns what it showed. GtkPrintUnixDialog keeps landscape (verified).

The page setup dialog also fills its paper list asynchronously. ClassicPrinting therefore reapplies the setup after the dialog is presented and passes the named GTK paper (for example `na_letter`) when its size matches. Without this, an untouched accept returned the locale default (`iso_a4`) with A4 default margins.

## Upstream candidate

**CW2-PRINT-001** in `upstream-issues/classic-wave2-printing/` is an author observation; independent review is pending.

- **Defect.** pdf 2.4.6 `PDFGraphics.FillPath`/`StrokePath` always fail with libharu 4177 (0x1051).
- **Hypothesis.** The package sets colour and width after the path is built.
- **Broader impact.** After the failure the path stays open, so later `FillRect`/`DrawString` calls on that page also fail. A new page still works.
- **Workaround.** Pages are created with `HPDF_AddPage` plus the size shims and wrapped with the public `PDFGraphics` constructor. Polygons and pen sweeps are filled through the same exported symbols, with the colour set first; no stroke path is used.
- **Removal rule.** Once every line of `repro.bui` prints `ok`, `FillPolygon` may return to `FillPath`.

## Verification (2026-10-31, Buoy 0.72.0, Linux x86_64 host)

Maintainers run the private validation suite before release. See the repository README for public build instructions.

**Setup.**

- The script stages the module, `ClassicGraphics.bui`, the test and copies of `/usr/share/buoy/packages` in a private temporary directory.
- It runs `buoy --check --diagnostic-format json` for the module and the test on all six targets (x86_64/arm64 × linux/darwin/windows). That is 12 checks, each with 0 errors; the only warning is the known upstream `XojoDesktop.bui:160`.
- It builds x86_64 Linux and runs everything in `buoy-pdf-test:local` with `--network none`, a unique container name, private `dbus-run-session` + `xvfb-run` and Openbox. That image is the local GUI runtime plus poppler-utils.

**Modes.** All nine passed.

- **pdf.** Unit assertions cover these areas:
  - setup geometry at 72 and 300 dpi
  - landscape swap
  - validation that leaves state unchanged
  - `SetupString` round trip
  - StringWidth against the AFM widths
  - every rejection listed above
  - finish, cancel and state errors

  It also covers NaN/Inf rejection for rects, lines, polygons, pictures, text and ovals, TextSize > 600, `-1` resolution, malformed JSON, and the atomic landscape rejection.

  The verifier then independently inspects the PDFs:
  - 3 pages, each 842×595 (A4 landscape)
  - one page's text per page, no cross-page leakage
  - Helvetica and Times-Bold fonts
  - pixels rasterized at 144 dpi at the expected physical positions, checking:
    - the margin origin and 300-dpi scaling
    - the red fill
    - natural-size and cropped pictures
    - the filled triangle
    - the inside-pen stroke

  A second file checks the 72-dpi Letter portrait origin.

  **Text files (1200/48, 600/73, 9600/12, 300×150/48).** `pdftotext -bbox` gives the word origin at 90 pt and the width as 1.112 em of the point size. Pixels are checked inside the first Helvetica I stem, between stems, above cap height and below the baseline.

  **lines.pdf (pen 8).** Rasters check:
  - the line start and the pen-hang end (101.5 and 206.5 black; 98.5 and 209.5 white)
  - the top and bottom of the line
  - the zero-length dot
  - the diagonal start/end pen corners and points off the line
  - a filled 8-wide `DrawRect` and a filled 8×8 `DrawOval`
  - polygon edges, a vertex pen corner and the apex, with the interior left unfilled
- **cups-unreachable.** With `CUPS_SERVER=127.0.0.1:9`, `OpenPrinter` raises `IOException`.
- **cups-none.** A mock IPP server with no queues returns Nil for the default and for a named queue, and no job is created.
- **cups-submit.** The mock queue records exactly two jobs over real libcups:
  - an explicit 3-page job, re-inspected with the same PDF checks
  - a 1-page job submitted by the destructor on scope exit

  It also checks:
  - titles
  - `application/pdf` format
  - the reported job ID matching the server's
  - that the cancelled job never reached the server
- **cups-fail.** The mock rejects Send-Document. The test sees `IOException`, the job is not reported as printed, resubmission is rejected, and the mock receives Cancel-Job for exactly that job. An empty title is rejected before submission.
- **dialog-cancel / setup-cancel.** Escape through XTEST input on the real GTK dialogs returns Nil/False, leaves the setup unchanged, and creates no output and no stray spool file.
- **setup-accept.** Alt+A accepts. Letter (`na_letter`) and the custom 30/20/40/50 margins survive.
- **dialog-print.** A landscape setup with margins 10/20/30/40 and "Print to File" preselected is accepted with Return. All four margins come back unchanged, along with the 752×552 printable area.
  - GTK's file backend writes a 2-page 792×612 PDF with the expected text, through the real `GtkPrintJob`.
  - The test also checks the landscape geometry, the default copies/range and spool-file cleanup.

**Not verified.** No physical printer, real cupsd, CUPS forwarding of copies/collate, avahi printers, or HiDPI pictures. macOS, Windows and arm64 Linux were checked by the compiler only. GUI tests used Xvfb, not a real desktop.

## Independent recheck and final validation fixes

Fresh Opus recheck confirmed the high-resolution text transforms, pen-hang
geometry, margin pairing, settings validation and scoped PDF path workaround.
It found a remaining infinite-pen validation gap. Pen validation now rejects
non-finite dimensions before comparison or geometry; Transparency rejects NaN
as well. Regressions cover infinite pens on lines/polygons/rectangles/ovals, NaN
pen dimensions and unchanged transparency after a rejected NaN assignment.
Parent revalidation passed 12 six-target checks and all nine isolated modes.
Physical-printer rotation/copies/collation and native foreign execution remain
unverified. Dialog-returned paper bounds, optional settings field types and
self-intersecting polygon fill-rule differences remain review advisories.

## Roadmap items

Completed for Linux:

- "Printer-backed Graphics, page advancement and finalization", via CUPS/GTK and spooler-independent PDF
- API 1 `OpenPrinter`/`OpenPrinterDialog`/`PrinterSetup`/`NextPage`
- native print/page-setup dialog cancel and accept

Remaining:

- Windows GDI printing
- macOS `NSPrintOperation`/PDF printing
- Unicode text through embedded CID fonts
- translucency via ExtGState
- wrapped text and font metrics
- a printer enumeration API
- unifying the CUPS/GTK code with the `printing` package once its API is stable (it currently prints text-only display lists)
