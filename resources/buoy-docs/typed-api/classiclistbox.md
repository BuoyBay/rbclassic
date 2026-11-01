---
title: "rbclassic \u00b7 ClassicListBox"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicListBox"]
dependencies: []
symbols: ["ClassicListBox"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicListBox

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicListBox

`Public Class ClassicListBox Inherits DesktopListBox Implements ClassicListNativeClient`

API 1 `ListBox`. ListIndex, Change, LastIndex, tags and Sort are tracked by row identity. On Linux a ClassicListNativeBridge adds DoubleClick, KeyDown with type-to-select, header clicks with sort indicators, HasHeading, column titles/widths/removal and SelectionMultiple; other platforms report those as unsupported (see notes/controls.md and notes/list-native.md).

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `NativeListAvailable` | `Boolean` | Yes | No | — | True when the native bridge is attached (Linux GTK). Without it, DoubleClick/KeyDown/HeaderPressed never fire and HasHeading = False, retitling, width changes, column removal and SelectionMultiple raise UnsupportedOperationException. |
| `ListCount` | `Integer` | Yes | No | — | API 1 `ListCount`. |
| `LastIndex` | `Integer` | Yes | No | — | API 1 `LastIndex`: the row most recently created by AddRow or InsertRow (-1 before any). Removal and sorting do not change it. |
| `LastAddedRowIndex` | `Integer` | Yes | No | — | — |
| `SelectionType` | `Integer` | No | No | — | API 1 `SelectionType`: SelectionSingle (default) or SelectionMultiple. Multiple needs the native bridge. Switching keeps the selected rows that the new mode can hold (the lowest one when going back to single) and raises Change only if rows were dropped. |
| `ListIndex` | `Integer` | No | No | — | API 1 `ListIndex`: the selected row, or the lowest selected row with SelectionMultiple. Assigning selects only that row (-1 deselects all) and raises Change when the selection differs. Out-of-range values raise OutOfBoundsException. |
| `SelectedRowIndex` | `Integer` | No | No | — | — |
| `SelCount` | `Integer` | Yes | No | — | API 1 `SelCount`: number of selected rows. |
| `Text` | `String` | Yes | No | — | API 1 `Text`: column 0 of ListIndex's row, "" with no selection. |
| `ColumnCount` | `Integer` | No | No | — | — |
| `HasHeading` | `Boolean` | No | No | — | API 1 `HasHeading`. Defaults to False, as in API 1. Hiding the header row needs the native bridge; without it the header is always shown, HasHeading reads True and assigning False raises UnsupportedOperationException. |
| `ColumnWidths` | `String` | No | No | — | API 1 `ColumnWidths`: comma-separated points, percentages ("25%") and relative shares ("*", "2*"); a blank entry leaves that column's width alone. Relative and percentage widths are recomputed when the list is resized. Needs the native bridge. |
| `SortedColumn` | `Integer` | No | No | — | API 1 `SortedColumn` (-1 = none). Assigning does not sort; call Sort. The native header indicator follows it. |

### Constants

| Name | Type | Value / Default | Description |
| --- | --- | --- | --- |
| `SortDescending` | `Integer` | `-1` | — |
| `SortNone` | `Integer` | `0` | — |
| `SortAscending` | `Integer` | `1` | — |
| `SelectionSingle` | `Integer` | `0` | — |
| `SelectionMultiple` | `Integer` | `1` | — |

### Constructor

`Public Sub Constructor()`

No parameters.

Returns: no value.

### ReloadData

`Public Overrides Sub ReloadData()`

No parameters.

Returns: no value.

### ReloadRow

`Public Overrides Sub ReloadRow(row As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `row` | `Integer` | `ByVal` | Required |

Returns: no value.

### ClassicListNativeActivated

`Public Sub ClassicListNativeActivated(row As Integer)`

Native row activation: a mouse double-click on GTK.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `row` | `Integer` | `ByVal` | Required |

Returns: no value.

### ClassicListNativeKey

`Public Function ClassicListNativeKey(keyval As Integer, codepoint As Integer, modifiers As Integer) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `keyval` | `Integer` | `ByVal` | Required |
| `codepoint` | `Integer` | `ByVal` | Required |
| `modifiers` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### ClassicListNativeHeader

`Public Sub ClassicListNativeHeader(column As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `column` | `Integer` | `ByVal` | Required |

Returns: no value.

### ClassicListNativeSelection

`Public Sub ClassicListNativeSelection()`

No parameters.

Returns: no value.

### ClassicListNativeResized

`Public Sub ClassicListNativeResized(width As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `width` | `Integer` | `ByVal` | Required |

Returns: no value.

### AddRow

`Public Overrides Sub AddRow(ParamArray items As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `items` | `String` | `ParamArray` | Required |

Returns: no value.

### AddRowItems

`Public Sub AddRowItems(items As Array Of String)`

API 1 `AddRow(items() As String)`: one column per element. Buoy cannot overload it beside the ParamArray form; rewrite to AddRowItems.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `items` | `Array Of String` | `ByVal` | Required |

Returns: no value.

### AddRowAt

`Public Overrides Sub AddRowAt(index As Integer, ParamArray items As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |
| `items` | `String` | `ParamArray` | Required |

Returns: no value.

### InsertRow

`Public Sub InsertRow(row As Integer, text As String, indent As Integer = 0)`

API 1 `InsertRow(row, text [, indent])`. Text goes to column 0; indent only affects hierarchical lists, which Buoy does not provide.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `row` | `Integer` | `ByVal` | Required |
| `text` | `String` | `ByVal` | Required |
| `indent` | `Integer` | `ByVal` | `0` |

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

### RemoveAllRows

`Public Overrides Sub RemoveAllRows()`

No parameters.

Returns: no value.

### DeleteAllRows

`Public Sub DeleteAllRows()`

API 1 `DeleteAllRows`.

No parameters.

Returns: no value.

### Selected

`Public Function Selected(row As Integer) As Boolean`

API 1 `Selected(row)`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `row` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### Selected (overload 2)

`Public Sub Selected(row As Integer, Assigns value As Boolean)`

With SelectionMultiple, adds or removes one row without touching the others; with SelectionSingle, True selects only that row. A change raises Change.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `row` | `Integer` | `ByVal` | Required |
| `value` | `Boolean` | `Assigns` | Required |

Returns: no value.

### List

`Public Function List(row As Integer) As String`

API 1 `List(row)`: column 0 of the row.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `row` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### List (overload 2)

`Public Sub List(row As Integer, Assigns value As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `row` | `Integer` | `ByVal` | Required |
| `value` | `String` | `Assigns` | Required |

Returns: no value.

### Cell

`Public Function Cell(row As Integer, column As Integer) As String`

API 1 `Cell(row, column)`. -1 selects all rows (EndOfLine-delimited) or all columns (tab-delimited).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `row` | `Integer` | `ByVal` | Required |
| `column` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### Cell (overload 2)

`Public Sub Cell(row As Integer, column As Integer, Assigns value As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `row` | `Integer` | `ByVal` | Required |
| `column` | `Integer` | `ByVal` | Required |
| `value` | `String` | `Assigns` | Required |

Returns: no value.

### Heading

`Public Function Heading(column As Integer) As String`

API 1 `Heading(column)`; Heading(-1) is every heading, tab-delimited.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `column` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### Heading (overload 2)

`Public Sub Heading(column As Integer, Assigns value As String)`

Headings can always be assigned before the native columns exist (the first row or ReloadData). After that, retitling needs the native bridge; without it a changed heading raises UnsupportedOperationException.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `column` | `Integer` | `ByVal` | Required |
| `value` | `String` | `Assigns` | Required |

Returns: no value.

### Column

`Public Function Column(index As Integer) As ClassicListColumn`

API 1 `Column(index)`: a ListColumn view of one column's width and resize behavior.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `ClassicListColumn` |

### ColumnWidthExpression

`Public Function ColumnWidthExpression(column As Integer) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `column` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### SetColumnWidthExpression

`Public Sub SetColumnWidthExpression(column As Integer, expression As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `column` | `Integer` | `ByVal` | Required |
| `expression` | `String` | `ByVal` | Required |

Returns: no value.

### ColumnWidthActual

`Public Function ColumnWidthActual(column As Integer) As Integer`

Actual native width in points (read back, so it includes a user drag).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `column` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### ColumnUserResizable

`Public Function ColumnUserResizable(column As Integer) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `column` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### SetColumnUserResizable

`Public Sub SetColumnUserResizable(column As Integer, value As Boolean)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `column` | `Integer` | `ByVal` | Required |
| `value` | `Boolean` | `ByVal` | Required |

Returns: no value.

### RowTag

`Public Function RowTag(row As Integer) As Variant`

API 1 `RowTag(row) As Variant`; unset tags are Variant.Empty().

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `row` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Variant` |

### RowTag (overload 2)

`Public Sub RowTag(row As Integer, Assigns value As Variant)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `row` | `Integer` | `ByVal` | Required |
| `value` | `Variant` | `Assigns` | Required |

Returns: no value.

### CellTag

`Public Function CellTag(row As Integer, column As Integer) As Variant`

API 1 `CellTag(row, column) As Variant`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `row` | `Integer` | `ByVal` | Required |
| `column` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Variant` |

### CellTag (overload 2)

`Public Sub CellTag(row As Integer, column As Integer, Assigns value As Variant)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `row` | `Integer` | `ByVal` | Required |
| `column` | `Integer` | `ByVal` | Required |
| `value` | `Variant` | `Assigns` | Required |

Returns: no value.

### ColumnSortDirection

`Public Function ColumnSortDirection(column As Integer) As Integer`

API 1 `ColumnSortDirection(column)`: SortAscending (default), SortNone or SortDescending.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `column` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### ColumnSortDirection (overload 2)

`Public Sub ColumnSortDirection(column As Integer, Assigns value As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `column` | `Integer` | `ByVal` | Required |
| `value` | `Integer` | `Assigns` | Required |

Returns: no value.

### PressHeader

`Public Sub PressHeader(column As Integer)`

API 1 `PressHeader(column)`: as if the header were clicked, raising HeaderPressed and sorting, but without reversing the direction.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `column` | `Integer` | `ByVal` | Required |

Returns: no value.

### Sort

`Public Sub Sort()`

API 1 `Sort()`: stable sort on SortedColumn in its ColumnSortDirection, after SortColumn (which may cancel). Rows keep their tags; selected rows stay selected and Change is not raised.

No parameters.

Returns: no value.
