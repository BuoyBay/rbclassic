---
title: "rbclassic \u00b7 ClassicPrinting functions"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: []
dependencies: []
symbols: ["ClassicOpenPDFPrinter", "OpenPrinter", "OpenPrinterDialog"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicPrinting functions

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicPrinting functions

### ClassicOpenPDFPrinter

`Public Function ClassicOpenPDFPrinter() As ClassicPrinterGraphics`

Buoy extension: a printer Graphics recorded as PDF on every platform. It contacts no print system; finish it and read ClassicPDFBytes.

No parameters.

#### Returns

| Type |
| --- |
| `ClassicPrinterGraphics` |

### ClassicOpenPDFPrinter (overload 2)

`Public Function ClassicOpenPDFPrinter(setup As ClassicPrinterSetup) As ClassicPrinterGraphics`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `setup` | `ClassicPrinterSetup` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `ClassicPrinterGraphics` |

### OpenPrinter

`Public Function OpenPrinter() As ClassicPrinterGraphics`

API 1 `OpenPrinter([setup])` without a dialog. Linux: targets `setup.ClassicPrinterName`, or the default CUPS queue, and returns Nil when CUPS reports no such queue. Unreachable CUPS raises IOException. macOS/Windows raise UnsupportedOperationException.

No parameters.

#### Returns

| Type |
| --- |
| `ClassicPrinterGraphics` |

### OpenPrinter (overload 2)

`Public Function OpenPrinter(setup As ClassicPrinterSetup) As ClassicPrinterGraphics`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `setup` | `ClassicPrinterSetup` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `ClassicPrinterGraphics` |

### OpenPrinterDialog

`Public Function OpenPrinterDialog() As ClassicPrinterGraphics`

API 1 `OpenPrinterDialog([setup], [parentWindow])`: the native GTK 4 print dialog (Linux). Returns Nil on cancel. On OK, the dialog's paper, orientation and margins are copied into `setup`, and the returned Graphics sends its PDF to the chosen printer.

No parameters.

#### Returns

| Type |
| --- |
| `ClassicPrinterGraphics` |

### OpenPrinterDialog (overload 2)

`Public Function OpenPrinterDialog(setup As ClassicPrinterSetup) As ClassicPrinterGraphics`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `setup` | `ClassicPrinterSetup` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `ClassicPrinterGraphics` |

### OpenPrinterDialog (overload 3)

`Public Function OpenPrinterDialog(setup As ClassicPrinterSetup, parentWindow As Window) As ClassicPrinterGraphics`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `setup` | `ClassicPrinterSetup` | `ByVal` | Required |
| `parentWindow` | `Window` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `ClassicPrinterGraphics` |
