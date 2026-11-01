---
title: "rbclassic \u00b7 ClassicComboBox"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicComboBox"]
dependencies: []
symbols: ["ClassicComboBox"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicComboBox

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicComboBox

`Public Class ClassicComboBox Inherits DesktopComboBox`

API 1 `ComboBox` (editable). ListIndex reads the native control, which reports -1 once the user types custom text; Text is read/write.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `ListCount` | `Integer` | Yes | No | — | API 1 `ListCount`. |
| `ListIndex` | `Integer` | No | No | — | API 1 `ListIndex`. A different value raises Change; out of range raises OutOfBoundsException. |
| `SelectedRowIndex` | `Integer` | No | No | — | — |

### Constructor

`Public Sub Constructor()`

No parameters.

Returns: no value.

### List

`Public Function List(index As Integer) As String`

API 1 `List(index)` (read-only).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### AddRow

`Public Overrides Sub AddRow(item As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `item` | `String` | `ByVal` | Required |

Returns: no value.

### AddRows

`Public Sub AddRows(items As Array Of String)`

API 1 `AddRows(items())`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `items` | `Array Of String` | `ByVal` | Required |

Returns: no value.

### InsertRow

`Public Sub InsertRow(index As Integer, item As String)`

API 1 `InsertRow(index, text)`; the selected item stays selected and typed text is kept.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |
| `item` | `String` | `ByVal` | Required |

Returns: no value.

### RemoveRowAt

`Public Overrides Sub RemoveRowAt(index As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

Returns: no value.

### RemoveRow

`Public Sub RemoveRow(index As Integer)`

API 1 `RemoveRow(index)`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

Returns: no value.

### RemoveAllItems

`Public Overrides Sub RemoveAllItems()`

No parameters.

Returns: no value.

### DeleteAllRows

`Public Sub DeleteAllRows()`

API 1 `DeleteAllRows` (does not raise Change; typed text is kept).

No parameters.

Returns: no value.

### RowTag

`Public Function RowTag(index As Integer) As Variant`

API 1 `RowTag(index) As Variant`; unset tags are Variant.Empty().

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Variant` |

### RowTag (overload 2)

`Public Sub RowTag(index As Integer, Assigns value As Variant)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |
| `value` | `Variant` | `Assigns` | Required |

Returns: no value.
