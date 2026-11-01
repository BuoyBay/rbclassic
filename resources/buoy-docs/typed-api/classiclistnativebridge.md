---
title: "rbclassic \u00b7 ClassicListNativeBridge"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicListNativeBridge"]
dependencies: []
symbols: ["ClassicListNativeBridge"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicListNativeBridge

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicListNativeBridge

`Public Class ClassicListNativeBridge`

Connects one Buoy ListBox's native widget to a ClassicListNativeClient. Every setter returns False (and changes nothing) when the native operation is unavailable, so callers can raise a truthful error.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `Attached` | `Boolean` | Yes | No | — | True after a successful Attach on a platform this bridge supports. |
| `Multiple` | `Boolean` | Yes | No | — | — |

### Constructor

`Public Sub Constructor(owner As Object)`

`owner` must implement ClassicListNativeClient. It is passed as Object because CType(interfaceRef, Object) raises IllegalCastException in Buoy 0.72 (upstream-issues/classic-wave2-listbox LISTBOX-001).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `owner` | `Object` | `ByVal` | Required |

Returns: no value.

### Attach

`Public Function Attach(nativeWidget As Ptr) As Boolean`

Bind to a ListBox's NativeWidget. Returns False when the widget is not the expected native structure or the platform is not bridged.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `nativeWidget` | `Ptr` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### Destructor

`Public Sub Destructor()`

No parameters.

Returns: no value.

### NativeActivated

`Public Sub NativeActivated(row As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `row` | `Integer` | `ByVal` | Required |

Returns: no value.

### NativeKey

`Public Function NativeKey(keyval As Integer, modifiers As Integer) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `keyval` | `Integer` | `ByVal` | Required |
| `modifiers` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### Contains

`Public Function Contains(widget As Ptr) As Boolean`

True when `widget` is this list's view or inside it.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `widget` | `Ptr` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### NativeKeyReleased

`Public Sub NativeKeyReleased()`

No parameters.

Returns: no value.

### NativeSorterChanged

`Public Sub NativeSorterChanged()`

No parameters.

Returns: no value.

### NativeSelectionChanged

`Public Sub NativeSelectionChanged(model As Ptr)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `model` | `Ptr` | `ByVal` | Required |

Returns: no value.

### NativeResized

`Public Sub NativeResized()`

No parameters.

Returns: no value.

### NativeColumnCount

`Public Function NativeColumnCount() As Integer`

Number of native columns (visible or hidden).

No parameters.

#### Returns

| Type |
| --- |
| `Integer` |

### SetColumnTitle

`Public Function SetColumnTitle(index As Integer, title As String) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |
| `title` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### ColumnTitle

`Public Function ColumnTitle(index As Integer) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### SetColumnWidth

`Public Function SetColumnWidth(index As Integer, width As Integer) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |
| `width` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### ColumnWidth

`Public Function ColumnWidth(index As Integer) As Integer`

Native fixed width (GTK updates it when the user drags a resizable column edge); -1 when unavailable.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### SetColumnVisible

`Public Function SetColumnVisible(index As Integer, visible As Boolean) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |
| `visible` | `Boolean` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### ColumnVisible

`Public Function ColumnVisible(index As Integer) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### SetColumnResizable

`Public Function SetColumnResizable(index As Integer, resizable As Boolean) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |
| `resizable` | `Boolean` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### ColumnResizable

`Public Function ColumnResizable(index As Integer) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### SetColumnClickable

`Public Function SetColumnClickable(index As Integer, clickable As Boolean) As Boolean`

Make a header clickable. The sorter compares nothing: GTK uses it only to toggle the header indicator and report the click, and the Buoy row store is never re-ordered by GTK.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |
| `clickable` | `Boolean` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### SetSortIndicator

`Public Function SetSortIndicator(column As Integer, direction As Integer) As Boolean`

Show the header sort indicator: direction 1 ascending, -1 descending; column -1 or direction 0 clears it.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `column` | `Integer` | `ByVal` | Required |
| `direction` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### SortIndicatorColumn

`Public Function SortIndicatorColumn() As Integer`

Header indicator state read back from GTK: the primary sorted column (-1 none) and its direction (1 ascending, -1 descending).

No parameters.

#### Returns

| Type |
| --- |
| `Integer` |

### SetHeaderVisible

`Public Function SetHeaderVisible(visible As Boolean) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `visible` | `Boolean` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### HeaderVisible

`Public Function HeaderVisible() As Boolean`

No parameters.

#### Returns

| Type |
| --- |
| `Boolean` |

### VisibleWidth

`Public Function VisibleWidth() As Integer`

Current width of the scrolled list (0 before it is allocated).

No parameters.

#### Returns

| Type |
| --- |
| `Integer` |

### SetMultiple

`Public Function SetMultiple(multiple As Boolean) As Boolean`

Swap the column view between the runtime's GtkSingleSelection and a GtkMultiSelection over the same row store. The runtime keeps reading its single selection, so the client owns the multiple-selection set.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `multiple` | `Boolean` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### SelectedRows

`Public Function SelectedRows() As Array Of Integer`

Selected native positions in ascending order (multiple mode only).

No parameters.

#### Returns

| Type |
| --- |
| `Array Of Integer` |

### SelectRows

`Public Function SelectRows(rows As Array Of Integer) As Boolean`

Replace the native multiple selection without notifying the client.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `rows` | `Array Of Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |
