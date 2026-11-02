# ClassicPrinting implementation notes

- `modules/ClassicPrinting.bui`
- at the repo root
- this note
- the runtime compatibility boundary

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

- **Package.** `pdf` 2.4.6 ships `libpdf` for all six targets. Every program that imports the module therefore links `libpdf`. This dependency applies to the `RBClassic` entry.
- **Native libraries.** None are added at build time. Linux libraries are loaded at run time through `Optional Declare`:
  - `libcups.so.2`
  - `libgtk-4.so.1`
  - `libgobject-2.0.so.0`
  - `libglib-2.0.so.0`
  - libc
- **Missing libraries.** A missing library raises `LibraryUnavailableException` only when that path is used. PDF jobs need none of them.
- **Source and payload.** The module is source-only, with no owned native payload.
- **Exported libpdf symbols.** The module also binds symbols from `Lib "pdf"`. These are pinned to the pdf 2.4.6 shim names, so verify symbol compatibility when upgrading the pdf package.

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

## Runtime boundary

- **Defect.** pdf 2.4.6 `PDFGraphics.FillPath`/`StrokePath` always fail with libharu 4177 (0x1051).
- **Hypothesis.** The package sets colour and width after the path is built.
- **Broader impact.** After the failure the path stays open, so later `FillRect`/`DrawString` calls on that page also fail. A new page still works.
- **Workaround.** Pages are created with `HPDF_AddPage` plus the size shims and wrapped with the public `PDFGraphics` constructor. Polygons and pen sweeps are filled through the same exported symbols, with the colour set first; no stroke path is used.
- **Removal rule.** Once every line of `repro.bui` prints `ok`, `FillPolygon` may return to `FillPath`.

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
