---
title: "rbclassic \u00b7 ClassicPrinterGraphics"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicPrinterGraphics"]
dependencies: []
symbols: ["ClassicPrinterGraphics"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicPrinterGraphics

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicPrinterGraphics

`Public Class ClassicPrinterGraphics`

API 1 printer `Graphics`. Pages are vector PDF in the setup's device units: (0, 0) is the printable origin and one unit is 1/resolution inch.  Lifecycle: draw, `NextPage()` between pages, then either call `ClassicFinishPrinting()` (Buoy extension: submits and reports errors) or drop the last reference — the destructor submits a printer job, as legacy sends the job when its Graphics goes out of scope, but errors there can only be swallowed. `ClassicCancelPrinting()` discards every page.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `TextFont` | `String` | No | No | `"System"` | API 1 `TextFont` (default "System" = Helvetica in PDF output). |
| `TextSize` | `Double` | No | No | `12.0` | API 1 `TextSize` in points regardless of resolution (0 = 12; at most 600). |
| `PenWidth` | `Double` | No | No | `1.0` | API 1 `PenWidth` in device units (default 1). |
| `PenHeight` | `Double` | No | No | `1.0` | API 1 `PenHeight`; strokes need PenHeight = PenWidth. |
| `Bold` | `Boolean` | No | No | `False` | — |
| `Italic` | `Boolean` | No | No | `False` | — |
| `Underline` | `Boolean` | No | No | `False` | — |
| `ClassicJobTitle` | `String` | No | No | `"Buoy print job"` | Buoy extension: job title passed to CUPS/GTK. |
| `ForeColor` | `Color` | No | No | — | API 1 `ForeColor` (default black). Translucent colors raise when used: the PDF backend cannot write alpha for solid drawing. |
| `Transparency` | `Double` | No | No | — | API 1 `Transparency` (0-100). Nonzero values raise when drawing shapes, text or pictures (pictures keep only their own alpha). |
| `Width` | `Integer` | Yes | No | — | API 1 `Width`: printable width in device units. |
| `Height` | `Integer` | Yes | No | — | API 1 `Height`: printable height in device units. |
| `Copies` | `Integer` | Yes | No | — | API 1 `Copies`. GTK jobs send the dialog's copy count to the print system, so this is 1 (as legacy documents for macOS). |
| `FirstPage` | `Integer` | Yes | No | — | API 1 `FirstPage`: first page of the dialog's range (1 otherwise). |
| `LastPage` | `Integer` | Yes | No | — | API 1 `LastPage`: last page of the dialog's range; 0 means "all pages". |
| `PrintingCancelled` | `Boolean` | Yes | No | — | API 1 `PrintingCancelled`: True after ClassicCancelPrinting. |
| `ClassicPageCount` | `Integer` | Yes | No | — | Buoy extension: pages recorded so far (the current page included). |
| `ClassicDestination` | `ClassicPrintDestination` | Yes | No | — | — |
| `ClassicPrinterName` | `String` | Yes | No | — | Buoy extension: CUPS queue or GTK printer name ("" for PDF). |
| `ClassicJobId` | `Integer` | Yes | No | — | Buoy extension: CUPS job id after a successful CUPS submission, else 0. |
| `ClassicFinished` | `Boolean` | Yes | No | — | Buoy extension: True once ClassicFinishPrinting succeeded. |

### Destructor

`Public Sub Destructor()`

No parameters.

Returns: no value.

### ClassicPDFBytes

`Public Function ClassicPDFBytes() As Bytes`

Buoy extension: the finished PDF of a PDF-destination job.

No parameters.

#### Returns

| Type |
| --- |
| `Bytes` |

### ClassicLoadFont

`Public Sub ClassicLoadFont(f As FileSystemItem, name As String)`

Buoy extension: embeds a TrueType font usable as `TextFont = name`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `f` | `FileSystemItem` | `ByVal` | Required |
| `name` | `String` | `ByVal` | Required |

Returns: no value.

### NextPage

`Public Sub NextPage()`

API 1 `NextPage`: ends the current page and starts a new one.

No parameters.

Returns: no value.

### ClassicCancelPrinting

`Public Sub ClassicCancelPrinting()`

Buoy extension: discards every page; nothing is submitted.

No parameters.

Returns: no value.

### ClassicFinishPrinting

`Public Sub ClassicFinishPrinting()`

Buoy extension: finishes the last page and submits the document (or, for PDF jobs, makes ClassicPDFBytes available). Errors raise and leave the job failed; it is never retried or reported as printed.

No parameters.

Returns: no value.

### DrawLine

`Public Sub DrawLine(x1 As Double, y1 As Double, x2 As Double, y2 As Double)`

API 1 `DrawLine`. The pen hangs right/below the coordinates, as on legacy raster contexts: the p x p pen square swept from (x1, y1) to (x2, y2) is filled, so a horizontal line covers x1..x2+p and a zero-length line is a p x p dot.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `x1` | `Double` | `ByVal` | Required |
| `y1` | `Double` | `ByVal` | Required |
| `x2` | `Double` | `ByVal` | Required |
| `y2` | `Double` | `ByVal` | Required |

Returns: no value.

### DrawRect

`Public Sub DrawRect(x As Double, y As Double, width As Double, height As Double)`

API 1 `DrawRect`: the outline lies inside (x, y, width, height).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `width` | `Double` | `ByVal` | Required |
| `height` | `Double` | `ByVal` | Required |

Returns: no value.

### FillRect

`Public Sub FillRect(x As Double, y As Double, width As Double, height As Double)`

API 1 `FillRect` covering exactly width x height device units.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `width` | `Double` | `ByVal` | Required |
| `height` | `Double` | `ByVal` | Required |

Returns: no value.

### DrawOval

`Public Sub DrawOval(x As Double, y As Double, width As Double, height As Double)`

API 1 `DrawOval`: the outline lies inside the bounds.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `width` | `Double` | `ByVal` | Required |
| `height` | `Double` | `ByVal` | Required |

Returns: no value.

### FillOval

`Public Sub FillOval(x As Double, y As Double, width As Double, height As Double)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `width` | `Double` | `ByVal` | Required |
| `height` | `Double` | `ByVal` | Required |

Returns: no value.

### DrawRoundRect

`Public Sub DrawRoundRect(x As Double, y As Double, width As Double, height As Double, arcWidth As Double, arcHeight As Double)`

API 1 `DrawRoundRect`; the arc is the corner radius, as in ClassicGraphics.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `width` | `Double` | `ByVal` | Required |
| `height` | `Double` | `ByVal` | Required |
| `arcWidth` | `Double` | `ByVal` | Required |
| `arcHeight` | `Double` | `ByVal` | Required |

Returns: no value.

### FillRoundRect

`Public Sub FillRoundRect(x As Double, y As Double, width As Double, height As Double, arcWidth As Double, arcHeight As Double)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `width` | `Double` | `ByVal` | Required |
| `height` | `Double` | `ByVal` | Required |
| `arcWidth` | `Double` | `ByVal` | Required |
| `arcHeight` | `Double` | `ByVal` | Required |

Returns: no value.

### DrawPolygon

`Public Sub DrawPolygon(points As Array Of Double)`

API 1 `DrawPolygon(points())` (1-based x, y pairs). Each closed edge is drawn like DrawLine: the pen square hangs right/below the vertices.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `points` | `Array Of Double` | `ByVal` | Required |

Returns: no value.

### DrawPolygon (overload 2)

`Public Sub DrawPolygon(points As Array Of Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `points` | `Array Of Integer` | `ByVal` | Required |

Returns: no value.

### FillPolygon

`Public Sub FillPolygon(points As Array Of Double)`

API 1 `FillPolygon(points())` (1-based x, y pairs).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `points` | `Array Of Double` | `ByVal` | Required |

Returns: no value.

### FillPolygon (overload 2)

`Public Sub FillPolygon(points As Array Of Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `points` | `Array Of Integer` | `ByVal` | Required |

Returns: no value.

### DrawString

`Public Sub DrawString(text As String, x As Double, y As Double, wrapWidth As Double = 0.0, condense As Boolean = False)`

API 1 `DrawString(text, x, y)`: one line, `y` is the baseline. A positive wrapWidth (wrap/condense) raises UnsupportedOperationException.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `text` | `String` | `ByVal` | Required |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `wrapWidth` | `Double` | `ByVal` | `0.0` |
| `condense` | `Boolean` | `ByVal` | `False` |

Returns: no value.

### StringWidth

`Public Function StringWidth(text As String) As Double`

API 1 `StringWidth` in device units, from the PDF font metrics.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `text` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### DrawPicture

`Public Sub DrawPicture(image As Picture, x As Double, y As Double)`

API 1 `DrawPicture(image, x, y)` at natural size (1 pixel = 1 device unit).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `image` | `Picture` | `ByVal` | Required |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |

Returns: no value.

### DrawPicture (overload 2)

`Public Sub DrawPicture(image As Picture, x As Double, y As Double, destWidth As Double, destHeight As Double)`

API 1 5-argument `DrawPicture` crops to the top-left destW x destH region.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `image` | `Picture` | `ByVal` | Required |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `destWidth` | `Double` | `ByVal` | Required |
| `destHeight` | `Double` | `ByVal` | Required |

Returns: no value.

### DrawPicture (overload 3)

`Public Sub DrawPicture(image As Picture, x As Double, y As Double, destWidth As Double, destHeight As Double, sourceX As Double, sourceY As Double, sourceWidth As Double, sourceHeight As Double)`

API 1 9-argument `DrawPicture`: scales the source rectangle into the destination.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `image` | `Picture` | `ByVal` | Required |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `destWidth` | `Double` | `ByVal` | Required |
| `destHeight` | `Double` | `ByVal` | Required |
| `sourceX` | `Double` | `ByVal` | Required |
| `sourceY` | `Double` | `ByVal` | Required |
| `sourceWidth` | `Double` | `ByVal` | Required |
| `sourceHeight` | `Double` | `ByVal` | Required |

Returns: no value.

### DrawPicture (overload 4)

`Public Sub DrawPicture(image As ClassicPicture, x As Double, y As Double)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `image` | `ClassicPicture` | `ByVal` | Required |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |

Returns: no value.

### DrawPicture (overload 5)

`Public Sub DrawPicture(image As ClassicPicture, x As Double, y As Double, destWidth As Double, destHeight As Double)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `image` | `ClassicPicture` | `ByVal` | Required |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `destWidth` | `Double` | `ByVal` | Required |
| `destHeight` | `Double` | `ByVal` | Required |

Returns: no value.

### DrawPicture (overload 6)

`Public Sub DrawPicture(image As ClassicPicture, x As Double, y As Double, destWidth As Double, destHeight As Double, sourceX As Double, sourceY As Double, sourceWidth As Double, sourceHeight As Double)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `image` | `ClassicPicture` | `ByVal` | Required |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `destWidth` | `Double` | `ByVal` | Required |
| `destHeight` | `Double` | `ByVal` | Required |
| `sourceX` | `Double` | `ByVal` | Required |
| `sourceY` | `Double` | `ByVal` | Required |
| `sourceWidth` | `Double` | `ByVal` | Required |
| `sourceHeight` | `Double` | `ByVal` | Required |

Returns: no value.
