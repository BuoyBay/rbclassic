---
title: "rbclassic \u00b7 ClassicPopupMenu"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicPopupMenu"]
dependencies: []
symbols: ["ClassicPopupMenu"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicPopupMenu

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicPopupMenu

`Public Class ClassicPopupMenu Inherits DesktopPopupMenu`

API 1 `PopupMenu`. The selection is tracked here because native pick-only combos auto-select item 0 when items are added and reset on rebuild; API 1 lists start at ListIndex -1.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `ListCount` | `Integer` | Yes | No | — | API 1 `ListCount`. |
| `ListIndex` | `Integer` | No | No | — | API 1 `ListIndex`; -1 = no selection. Out of range raises OutOfBoundsException. A different value raises Change. |
| `SelectedRowIndex` | `Integer` | No | No | — | — |
| `Text` | `String` | Yes | No | — | — |

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

API 1 `InsertRow(index, text)`; the selected item stays selected.

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

API 1 `DeleteAllRows` (does not raise Change).

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
