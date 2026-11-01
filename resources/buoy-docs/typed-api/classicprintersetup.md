---
title: "rbclassic \u00b7 ClassicPrinterSetup"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicPrinterSetup"]
dependencies: []
symbols: ["ClassicPrinterSetup"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicPrinterSetup

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicPrinterSetup

`Public Class ClassicPrinterSetup`

API 1 `PrinterSetup`, renamed so it cannot collide with the separate `printing` package's macOS `PrinterSetup`. Geometry is a portable model: paper size (portrait points), orientation, margins (points, relative to the oriented page) and drawing resolution. Defaults: US Letter, portrait, 18-point margins, 72 dpi — Buoy defaults, not values read from a driver.  Integer properties follow legacy's printer-coordinate contract in device units at `HorizontalResolution`/`VerticalResolution`: `Left`/`Top` are 0 (the printable origin), `PageLeft`/`PageTop` are the negative margins.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `Landscape` | `Boolean` | No | No | — | API 1 `Landscape` (read/write). Swaps the oriented page dimensions. |
| `ClassicPageWidthPoints` | `Double` | Yes | No | — | Oriented page width in points. |
| `ClassicPageHeightPoints` | `Double` | Yes | No | — | Oriented page height in points. |
| `ClassicLeftMargin` | `Double` | Yes | No | — | — |
| `ClassicTopMargin` | `Double` | Yes | No | — | — |
| `ClassicRightMargin` | `Double` | Yes | No | — | — |
| `ClassicBottomMargin` | `Double` | Yes | No | — | — |
| `ClassicPaperName` | `String` | Yes | No | — | Native paper identifier recorded from the last page-setup/print dialog. |
| `ClassicPrinterName` | `String` | No | No | — | Buoy extension: CUPS queue / GTK printer name. Empty means the default queue for `OpenPrinter`; the dialog preselects a nonempty name. |
| `PageWidth` | `Integer` | Yes | No | — | API 1 `PageWidth`: full oriented page width in device units. |
| `PageHeight` | `Integer` | Yes | No | — | API 1 `PageHeight`: full oriented page height in device units. |
| `Width` | `Integer` | Yes | No | — | API 1 `Width`: printable width (page minus margins) in device units. |
| `Height` | `Integer` | Yes | No | — | API 1 `Height`: printable height (page minus margins) in device units. |
| `Left` | `Integer` | Yes | No | — | API 1 `Left`: printable origin, always 0. |
| `Top` | `Integer` | Yes | No | — | API 1 `Top`: printable origin, always 0. |
| `PageLeft` | `Integer` | Yes | No | — | API 1 `PageLeft`: negative offset from the printable origin to the paper edge. |
| `PageTop` | `Integer` | Yes | No | — | API 1 `PageTop`: negative offset from the printable origin to the paper edge. |
| `HorizontalResolution` | `Integer` | Yes | No | — | API 1 `HorizontalResolution` in dots per inch of the drawing coordinates. |
| `VerticalResolution` | `Integer` | Yes | No | — | API 1 `VerticalResolution` in dots per inch of the drawing coordinates. |
| `MaxHorizontalResolution` | `Integer` | No | No | — | API 1 `MaxHorizontalResolution` request (1-9600). Output is vector PDF, so the request is granted exactly; read HorizontalResolution back. legacy's -1 ("highest possible resolution of the output device") raises UnsupportedOperationException: no backend here reports a driver maximum. |
| `MaxVerticalResolution` | `Integer` | No | No | — | API 1 `MaxVerticalResolution` request (1-9600), granted exactly. |
| `SetupString` | `String` | No | No | — | API 1 `SetupString`: versioned Buoy JSON (not a legacy/driver blob). It stores geometry, resolution, paper name and printer name only. Invalid input raises before any field changes. |
| `Settings` | `String` | No | No | — | API 2 name for `SetupString`. |

### Constructor

`Public Sub Constructor()`

No parameters.

Returns: no value.

### ClassicSetPaperSize

`Public Sub ClassicSetPaperSize(widthPoints As Double, heightPoints As Double)`

Buoy extension: portrait paper size in points (1-14400 each).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `widthPoints` | `Double` | `ByVal` | Required |
| `heightPoints` | `Double` | `ByVal` | Required |

Returns: no value.

### ClassicSetMargins

`Public Sub ClassicSetMargins(leftPoints As Double, topPoints As Double, rightPoints As Double, bottomPoints As Double)`

Buoy extension: margins in points relative to the oriented page.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `leftPoints` | `Double` | `ByVal` | Required |
| `topPoints` | `Double` | `ByVal` | Required |
| `rightPoints` | `Double` | `ByVal` | Required |
| `bottomPoints` | `Double` | `ByVal` | Required |

Returns: no value.

### PageSetupDialog

`Public Function PageSetupDialog() As Boolean`

API 1 `PageSetupDialog`: native modal page setup (Linux GTK 4 only). Returns False on cancel with every setting unchanged.

No parameters.

#### Returns

| Type |
| --- |
| `Boolean` |

### PageSetupDialog (overload 2)

`Public Function PageSetupDialog(parentWindow As Window) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `parentWindow` | `Window` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### ShowPageSetupDialog

`Public Function ShowPageSetupDialog() As Boolean`

API 2 name for `PageSetupDialog`.

No parameters.

#### Returns

| Type |
| --- |
| `Boolean` |

### ShowPageSetupDialog (overload 2)

`Public Function ShowPageSetupDialog(parentWindow As Window) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `parentWindow` | `Window` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### ShowPrinterDialog

`Public Function ShowPrinterDialog() As ClassicPrinterGraphics`

API 2 `ShowPrinterDialog`: same as `OpenPrinterDialog(Me, parentWindow)`.

No parameters.

#### Returns

| Type |
| --- |
| `ClassicPrinterGraphics` |

### ShowPrinterDialog (overload 2)

`Public Function ShowPrinterDialog(parentWindow As Window) As ClassicPrinterGraphics`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `parentWindow` | `Window` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `ClassicPrinterGraphics` |
