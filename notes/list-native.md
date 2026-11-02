# ClassicListNative — native ListBox bridge

Module: `modules/ClassicListNative.bui` (`Import RBFoundation` only; it does not
import `ClassicControls` or the entry module). Consumer:
`ClassicListBox` in `ClassicControls.bui`. Tests:
.

## Exports

- `Public Interface ClassicListNativeClient`: `ClassicListNativeActivated`,
  `ClassicListNativeKey`, `ClassicListNativeHeader`,
  `ClassicListNativeSelection`, `ClassicListNativeResized`.
  `ClassicListBox` implements it, so these appear as public members of
  `ClassicListBox`. They are bridge entry points, not API 1 members; the
  application routes them from native GTK signals.
- `Public Class ClassicListNativeBridge`: `Attach(nativeWidget)`, column
  title/width/visibility/resizable/clickable setters and getters, the sort
  indicator, header visibility, `SetMultiple`, `SelectedRows`, `SelectRows`
  and `VisibleWidth`. Every setter returns False and changes nothing when the
  platform has no bridge.
- No module-level Public functions, so no selective `.{ … }` import is
  needed. `Import ClassicControls` alone is enough for `ClassicListBox`; a
  test or consumer that names the bridge types imports `ClassicListNative`.
  The entry module may `Public Import ClassicListNative`; that is the
  parent's decision.

No native payload or extra package: the bridge uses `Optional Declare`
against the GTK 4/GLib libraries already loaded by Buoy's Linux runtime.

## Linux mechanism (public GTK 4 API only)

`ListBox.NativeWidget` is a `GtkScrolledWindow` whose child is the
`GtkColumnView`; `Attach` checks both GTypes and that the model is a
`GtkSingleSelection`, and returns False otherwise. Nothing depends on struct
offsets or private fields. The header row is found by walking the column
view's children for CSS name `header`.

| Feature | GTK hook |
|---|---|
| DoubleClick | `GtkColumnView::activate` (double-click with single-click-activate off). A Return/Enter that KeyDown did not consume also activates; the bridge flags it in key-pressed and drops that activation, clearing the flag on key release. |
| KeyDown, type-to-select | `GtkEventControllerKey` in the capture phase on the column view; `key-pressed` returns TRUE when KeyDown (or a type-select match) consumes the key. `gdk_keyval_to_unicode` gives the character. |
| HeaderPressed, indicator | each visible column gets an empty `GtkCustomSorter` (no compare function), which makes its header clickable. A click changes the view's `GtkColumnViewSorter`; its `changed` signal plus `gtk_column_view_sorter_get_primary_sort_column` identify the column. ClassicListBox sorts its own row store and pushes its state back with `gtk_column_view_sort_by_column` (bridge changes are masked). GTK never re-orders rows: the runtime's `GListStore` is not wrapped in a sort model. |
| HasHeading | `gtk_widget_set_visible` on the `header` child; survives `ReloadData` (probed). |
| Titles, widths, resizable | `gtk_column_view_column_set_title`, `set_fixed_width`, `set_resizable`; widths are read back with `get_fixed_width`, which GTK updates on a user drag. |
| Relative widths on resize | `changed` on the scrolled window's horizontal adjustment, filtered to real width changes of the widget. |
| Column removal | `gtk_column_view_column_set_visible(FALSE)` on trailing columns. The runtime's `ListBox.ColumnCount` is its own counter and a new native column binds the data index equal to that counter, so `gtk_column_view_remove_column` would bind later columns to the wrong data (probed: after a native removal, a new column still bound index 3 in position 2). Hiding keeps native index = data index; growing reuses hidden columns first. |
| SelectionMultiple | `gtk_column_view_set_model` with a `GtkMultiSelection` over the runtime's own `GListStore`, and back to the retained `GtkSingleSelection`. The runtime keeps reading its orphaned single selection (probed: no criticals, `ReloadData` does not reset the view's model), so ClassicListBox owns the selected-row set and listens to `selection-changed`. A reload clears the multi selection natively; ClassicListBox re-applies it. |

Lifetime: the bridge registers in a key→weak-reference table and passes the
key as signal user data, so callbacks after the ListBox is gone are no-ops.
`ClassicListNativeBridge` holds its client as `Weak Object` because `Weak`
accepts only classes and `CType(interfaceRef, Object)` aborts in 0.72
(a runtime compatibility boundary). It retains
the single-selection model and its multi-selection model, and releases both
in its destructor.

## Exact unsupported boundary

- macOS (`NSTableView` in an `NSScrollView`) and Windows (Buoy's custom grid,
  no native header) are not bridged: `Attach` returns False and
  ClassicListBox raises `UnsupportedOperationException` for every request it
  cannot show (see controls.md). A macOS bridge (header view removal, column
  title/width/hidden, `allowsMultipleSelection`, `doubleAction` with a
  registered target class) is feasible through the Objective-C runtime but
  untested here, so it is not shipped. Windows needs runtime support.
- Editable, checkbox and hierarchical cells are not implemented. Buoy's cells
  are data-source cells with Buoy child controls; a correct API 1 lifecycle
  (`CellClick` → `EditCell` → `CellTextChange`/`CellAction` →
  `CellLostFocus`, `CellCheck` ordering, `ExpandRow`/`CollapseRow` with
  `RowDepth`) needs per-cell event hooks the runtime does not expose, and a
  partial version would fake the ordering.
- `KeyUp`, `RowFromXY`/`ColumnFromXY`, `ColumnSortType`, column alignment
  and min/max widths are not provided.
- After the user drags a resizable column, a later list resize recomputes
  percent/star columns from their expressions, overwriting the dragged width
  of those columns (fixed-point columns are not touched).

## Roadmap items completed (Linux)

From ROADMAP "Native desktop work": ListBox row activation/double-click, key
events, header activation, header visibility, mutable column
geometry/titles/removal and multiple selection. Editable/checkbox/
hierarchical cells remain open.
