# ClassicControls — API 1 ListBox, PopupMenu, ComboBox and CheckBox

Module: `modules/ClassicControls.bui` (`Import RBFoundation`). Test:
.

## Exported globals

None. The module exports only classes (`ClassicListBox`, `ClassicListColumn`,
`ClassicPopupMenu`, `ClassicComboBox`, `ClassicCheckBox`,
`ClassicCompareResult`), so a plain `Public Import ClassicControls` is enough.
No selective `.{ … }` line is needed.

`ClassicControls` imports its sibling `ClassicListNative` (native ListBox
bridge, see [list-native.md](list-native.md)). `ClassicListBox` implements the
public `ClassicListNativeClient` interface from it. Consumers that only use
`ClassicListBox` need no extra import; the entry module may add
`Public Import ClassicListNative` if it wants to expose the bridge types.

## Source rewrites

Buoy's native `ListBox`, `Checkbox` and `ComboBox` own those names, so:

| API 1 source | Rewrite |
|---|---|
| `ListBox` / `PopupMenu` / `ComboBox` / `CheckBox` (Super, `As`, `New`) | `ClassicListBox` / `ClassicPopupMenu` / `ClassicComboBox` / `ClassicCheckBox` |
| `ListBox.SortAscending` etc. | `ClassicListBox.SortAscending` (class `Const`) |
| `CheckBox.CheckedStates.Checked` | `ClassicCheckBox.CheckedStates.Checked` |
| `CompareRows(row1, row2, column, ByRef result As Integer)`; `result = x` | `Handle CompareRows(row1 As Integer, row2 As Integer, column As Integer, outcome As ClassicCompareResult) As Boolean`; `outcome.Value = x` (Buoy events have no ByRef, and `Result` is a keyword) |
| `lb.AddRow(arrayOfStrings)` | `lb.AddRowItems(arrayOfStrings)` (a ParamArray and an array overload have the same signature in Buoy, and a ParamArray does not accept an array) |
| `ListBox.SelectionMultiple` / `SelectionSingle` | `ClassicListBox.SelectionMultiple` / `SelectionSingle` |
| `lb.Column(i).WidthActual` etc. | unchanged; `Column` returns a `ClassicListColumn` |

Every other API 1 member listed below keeps its exact name.

## Supported behavior

The sources are the archived docs.xojo.com pages (Wayback, 2016–2018) and the
deprecated-member pages on documentation.xojo.com.

**ClassicListBox** (over `DesktopListBox`)
- `ListCount`, `ListIndex`, `List(i)` get/set, `Cell(row, col)` get/set,
  `Heading(i)` get/set, `Text` (read-only), `Selected(row)` get/set, `SelCount`,
  `LastIndex`, `AddRow(ParamArray)`, `AddRowItems(array)`,
  `InsertRow(row, text [, indent])`, `RemoveRow`, `DeleteAllRows`,
  `RowTag(row)` / `CellTag(row, col)` as `Variant`, `SortedColumn`,
  `ColumnSortDirection(col)`, `Sort()`, `PressHeader(col)`, `ColumnCount`
  (starts at 1, as in API 1, limited to 1–256), `HasHeading`, `ColumnWidths`,
  `Column(i)` (`WidthActual`, `WidthExpression`, `UserResizable`),
  `SelectionType`, and the events `Change`, `CompareRows`, `DoubleClick`,
  `KeyDown`, `HeaderPressed` and `SortColumn`.
- Native-only members (DoubleClick, KeyDown, header clicks, hiding the
  header, retitling after rows exist, column widths, removing columns and
  SelectionMultiple) work where the native bridge is attached:
  `NativeListAvailable` is True on Linux (GTK). The exact mechanism and
  boundary are in [list-native.md](list-native.md).
- `Cell` accepts -1 for every row or every column. Rows are joined with
  `EndOfLine.Current`, and an assignment accepts CR, LF or CRLF. Columns are
  joined with tabs. `Cell(-1,-1) = text` gives the list the source's shape:
  rows are added or trimmed at the end, columns grow, and surviving rows keep
  their identity. `Heading(-1)` reads and writes tab-delimited headings.
- Rows are identity records, so row and cell tags stay with their row
  through insert, remove and sort. The selection is stored as row
  references, so `ListIndex` and `Selected` follow the selected rows when
  other rows are inserted, removed or sorted. These index shifts do not
  raise `Change`.
- `Change` fires for a user selection (including a click on a row that is
  already selected, if the native control reports it). It also fires when
  `ListIndex`, `SelectedRowIndex` or `Selected` is assigned a different
  selection (the archived ListBox.Change page: "a programmatic change to
  ListIndex also triggers the Change event"), and when a selected row is
  removed by `RemoveRow`, `DeleteAllRows` or a shrinking `Cell(-1,-1)`.
  Assigning the current value does not fire it.
- `SelectionType = SelectionMultiple`: `ListIndex` is the lowest selected
  row (documentation.xojo.com: "the number of the lowest selected row is
  returned"); assigning `ListIndex` selects only that row and -1 clears the
  selection; `Selected(row) = True/False` adds or removes one row; `SelCount`
  counts the rows. Native Ctrl/Shift clicks are read from GTK and raise
  `Change` once per changed set. Switching modes keeps the selection the new
  mode can hold (the lowest row when returning to single) and raises `Change`
  only when rows were dropped.
- `LastIndex` and `LastAddedRowIndex` are the last row created by `AddRow` or
  `InsertRow` (so `InsertRow(1, …)` gives 1). The Desktop wrapper's own
  value, RowCount - 1, is wrong after an insert. Removal and sorting do not
  change it, because the docs define it only in terms of add and insert.
- `Sort()` does nothing when `SortedColumn` is -1 or the column's direction
  is `SortNone`. Otherwise it raises `SortColumn(column)`; returning True
  cancels the sort (documentation.xojo.com: SortColumn fires for a header
  click "or the Sort method was called"). The default direction is
  `SortAscending`. The default comparison is case-insensitive
  `String.Compare`, which matches Xojo's case-insensitive string ordering, so
  numbers compare as text, as the docs warn. The sort is stable.
  `CompareRows` receives the row numbers from before the sort. The Desktop
  wrapper's String `RowTagAt` also follows the sort.
- A header click raises `HeaderPressed(column)`; returning True leaves
  `SortedColumn` unchanged and does not sort ("the column is not sorted and
  the SortedColumn property is not updated"). Otherwise the column becomes
  `SortedColumn` and `Sort` runs. Clicking the already sorted column again
  reverses its `ColumnSortDirection` (adapter behavior; the deprecated page
  does not spell out toggling). `PressHeader(column)` takes the same path
  without reversing the direction ("This method does not update the sort
  direction"). The native header indicator always shows `SortedColumn` and
  its direction, and is cleared for -1 or `SortNone`.
- `KeyDown(key)` receives the typed character, or the API 1 control codes
  for navigation keys: Left 28, Right 29, Up 30, Down 31, Home 1, End 4,
  PageUp 11, PageDown 12, Return 13, keypad Enter 3, Tab 9, Backspace 8,
  Delete 127, Esc 27. Returning True consumes the key before the native
  list navigates. An unconsumed printable key without Control/Alt/Super/Meta
  type-selects: keys typed within one second build a prefix, and the first
  row whose column 0 starts with it (case-insensitive) is selected through
  `ListIndex` (so `Change` fires). Return/Enter never counts as a
  `DoubleClick`.
- `DoubleClick` fires for a native double-click on a row; `ListIndex` is
  that row. It has no row/column parameters, as in API 1. `RowFromXY` and
  `ColumnFromXY` are not provided.
- `HasHeading` defaults to False, as in API 1, and hides the native header
  row. `Heading(i) = text` retitles the native column at any time.
- `ColumnCount` can shrink: the removed columns' cells, cell tags, headings,
  widths and sort state are discarded, and growing again starts them empty.
  `SortedColumn` resets to -1 if its column is removed.
- `ColumnWidths` accepts comma-separated points (`50`), percentages of the
  list width (`25%`) and relative shares of the rest (`*`, `2*`); a blank
  entry leaves that column's native width alone. Percent and share widths
  are recomputed when GTK reallocates the list. Invalid entries raise
  `InvalidArgumentException` without changing anything; more entries than
  columns raise `OutOfBoundsException`. `Column(i).WidthActual` reads the
  native width (including a user drag); assigning it sets that column's
  expression to the number of points. `Column(i).UserResizable` maps to the
  native resizable flag.
- Native `ReloadData`/`ReloadRow` on GTK clear the selection and raise a
  spurious `SelectionChanged`. Both are overridden to ignore that event and
  re-apply the logical selection, in both selection modes. This was verified
  by probe and covered by mutation tests.

**ClassicPopupMenu** (over `DesktopPopupMenu`)
- `ListCount`, `ListIndex`, `List(i)` (read-only, as in API 1), `Text`
  (read-only), `AddRow`, `AddRows(array)`, `InsertRow`, `RemoveRow`,
  `DeleteAllRows`, `RowTag(i)` as `Variant`, `SelectedRowIndex` (shadowed to
  the same model), and the `Change` event.
- A new list starts with `ListIndex = -1`. The native pick-only control
  selects item 0 automatically when items are added (GTK, verified), so the
  adapter undoes that. The selection and tags shift with inserts and removals
  above the selected item.
- `Change` fires when the user picks an item or when `ListIndex` is assigned
  a different value (forum reports for the API 1 desktop control). It does
  not fire for `DeleteAllRows`: Xojo forum reports say ListIndex becomes -1
  with no Change event. Removing the selected row is treated the same way:
  it clears the selection without raising Change.

**ClassicComboBox** (over `DesktopComboBox`, editable)
- Same members as the PopupMenu, plus read/write `Text` and a re-raised
  `TextChanged` event. API 1 ComboBox inherits `Change` (the selected item
  changed) from PopupMenu and adds `TextChanged`.
- `ListIndex` is read from the native control, so it reports -1 when the
  user has typed custom text. Inserting or removing a row keeps the
  selection, or the typed text when nothing is selected. Programmatic text
  changes and row edits do not raise events. DeleteAllRows preserves the visible text, including the formerly selected item text, while clearing ListIndex.

**ClassicCheckBox** (over `DesktopCheckBox`)
- `Value As Boolean` is reclaimed with `@Shadows` plus a setter that assigns
  through `Super.Value`. The old shim comment says `Super.Foo = value` does
  not parse, but that is out of date: inheritance.md documents it and the
  probe confirms it works. `Value` is True for Checked or Indeterminate.
  Assigning True selects Checked, even from Indeterminate, and assigning
  False selects Unchecked.
- `State As ClassicCheckBox.CheckedStates` and the API 2 `VisualState`.
- `Action` fires for a user toggle and for any programmatic change of state
  (the archived CheckBox.Action page: "clicked or the value has been changed
  programmatically"). Assigning the current state is silent.

## Limitations (explicit, not emulated)

- **No native bridge on macOS or Windows yet.** There, `NativeListAvailable`
  is False, `HasHeading` reads True (headers always show) and assigning False
  raises `UnsupportedOperationException`, as do retitling after rows are
  shown, `ColumnWidths`/`WidthActual`/`WidthExpression`/`UserResizable`
  assignment, shrinking `ColumnCount` and `SelectionMultiple`. `DoubleClick`,
  `KeyDown` and user `HeaderPressed` never fire there; `PressHeader` and
  `Sort` still work. Nothing is stored that the native control cannot show.
- `HasHeading` default: API 1's False is honored only where the bridge can
  hide the header.
- Headings: heading `""` is stored as empty; the docs' "default heading" is
  not modeled.
- `Cell(-1, col) = text` must have exactly one line per row, or it raises
  `InvalidArgumentException`. The archived docs do not specify what happens
  on a mismatch.
- An out-of-range `ListIndex` or row index raises `OutOfBoundsException`, and
  a negative column other than -1 does the same.
- **Not implemented:** `CellClick`, `CellAction`, `CellTextChange`,
  `CellGotFocus`/`CellLostFocus`, editable cells (`EditCell`, `CellType`,
  `ColumnType`), checkbox cells (`CellCheck`, `CellState`), hierarchical rows
  (`AddFolder`, `Expanded`, `RowDepth`, `ExpandRow`/`CollapseRow`; the
  `InsertRow` indent is accepted and ignored, as documented for
  non-hierarchical lists), `KeyUp`, `MouseDown`/`MouseUp` on the list,
  `RowFromXY`/`ColumnFromXY`, `ColumnAlignment`, min/max column widths,
  drag reorder, cell styling, `ScrollPosition`, `ColumnSortType`, and
  PopupMenu `AddSeparator`. Native cell editing and checkbox/hierarchical
  cells need per-cell widgets and event ordering that Buoy's data-source
  cells do not expose; see list-native.md.
- Writes made through the base-typed API (`ListBox.SelectedRow`,
  `ComboBox.SelectedIndex`, `Checkbox.Value`, or the inherited `IsOn`) skip
  the API 1 event logic, because Buoy properties are bound statically. Rows
  added through the public `Rows` array get fresh, empty tags. The inherited
  `HeaderAt(i) = text` updates the heading but reaches the native title only
  at the next reload; use `Heading(i)`.
- The inherited `DesktopListBox.RowTagAt` (String) is separate from the
  Variant `RowTag`.

## Runtime work still needed in the core

1. `ListBox`: a public double-click/activate event, key events, header-click
   events and a sort indicator, header visibility, column title/width
   setters, column removal and multi-row selection on every platform. This
   module bridges them on GTK only (list-native.md).
2. `ListBox`: column removal that keeps the data binding (the runtime binds a
   new column by its creation counter, so native removal would misalign
   data; ClassicListBox hides trailing columns instead).
3. `ListBox`: keep the selection through `ReloadData` (GTK clears it and
   raises a spurious SelectionChanged), or offer a row-identity-aware reload.
4. `ComboBox`: native insert and remove-at, separators, and pick-only
   creation without auto-selecting item 0.
5. macOS editable `ComboBox` raises SelectionChanged on programmatic sets
   (see xojo-shim-gaps). Synchronous raises are suppressed here; asynchronous
   ones would still reach `Change`. This is not verified on macOS or Windows.
