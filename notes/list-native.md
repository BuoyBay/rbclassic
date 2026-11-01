# ClassicListNative — native ListBox bridge

Module: `modules/ClassicListNative.bui` (`Import RBFoundation` only; it does not
import `ClassicControls` or the entry module). Consumer:
`ClassicListBox` in `ClassicControls.bui`. Tests:
`tests/classic_list_native_test.bui` and
`tests/classic_list_native_verify.py`.

## Exports

- `Public Interface ClassicListNativeClient`: `ClassicListNativeActivated`,
  `ClassicListNativeKey`, `ClassicListNativeHeader`,
  `ClassicListNativeSelection`, `ClassicListNativeResized`.
  `ClassicListBox` implements it, so these appear as public members of
  `ClassicListBox`. They are bridge entry points, not API 1 members; the
  native-state test calls two of them to stand in for GTK.
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
(candidate LISTBOX-001, `upstream-issues/classic-wave2-listbox`). It retains
the single-selection model and its multi-selection model, and releases both
in its destructor.

## Tests and results (Buoy 0.72.0, x86_64 Linux, `buoy:0.72.0-gui`)

Work in an isolated temp directory with the installed packages copied to
`packages/` and the module/test sources copied in. Both GUI tests (this one and
`classic_controls_test.bui`) make every GLib warning and critical fatal
(`g_log_set_always_fatal`), so they must be linked with the GTK lifecycle
guard. Buoy 0.72's window bridge connects an invalid `focus-out` signal on
every Window (BUI-007, already in the queue), and an unguarded build aborts on
that critical:

```sh
OBJ=$(python3 tools/build_gtklifecycle.py)   # or compile the guard into temp
buoy classic_list_native_test.bui -o classic_list_native_test --extra-obj="$OBJ"
docker run --rm --name lbn-$RANDOM --network none -v "$PWD:$PWD" -w "$PWD" \
  --entrypoint dbus-run-session buoy:0.72.0-gui -- timeout 90 xvfb-run -a \
  ./classic_list_native_test
docker run --rm --name lbn-$RANDOM --network none -v "$PWD:$PWD" -w "$PWD" \
  --entrypoint dbus-run-session buoy:0.72.0-gui -- timeout 90 xvfb-run -a \
  python3 classic_list_native_verify.py ./classic_list_native_test
```

`--extra-obj` applies to Linux builds only. The verifier starts the probe with
`GTK_A11Y=none`. Under `dbus-run-session -- xvfb-run`, the D-Bus-activated
AT-SPI services start without X authorization ("Authorization required",
"AT-SPI: Cannot open default display") and exit. GApplication then logs
`Gtk-CRITICAL: Unable to register the application: ... NoReply` when
`Application.Run` starts. A minimal Window + `Application.Run` program
reproduces it; with `GTK_A11Y=none` it is clean. This is the container
harness, not Buoy or the list code, and was previously hidden in stderr.
The native-state mode never calls `Application.Run` and needs no such
setting.

Results with the guard linked and GLib diagnostics fatal: both modes pass,
and the real-X mode passed in each of the final runs. Without the guard,
both tests and the real-X probe abort (exit 133, SIGTRAP) on the BUI-007
critical, as intended. So the list bridge itself (column-view controllers,
sorters, model swaps, column and header changes) emits no GLib warnings or
criticals.

- Native-state mode: `classic list native: ok`. The test reads GTK state
  through its own Declares, not the bridge: header visibility for an empty
  list, after rows and after reload; native titles after retitling; hidden,
  reused and new columns with their data; fixed widths for `50,25%,*` →
  50/100/250 and `2*,*,100` → 200/100/100 over 400 pt; `WidthActual`; the
  resizable flag; the sorter's primary column/order through Sort,
  PressHeader, header clicks, HeaderPressed and SortColumn cancellation, and
  SortNone; the view model's GType and `gtk_selection_model_is_selected` for
  multiple selection through Selected, AddRow (reload), Sort, RemoveRow,
  ListIndex and the switch back to single; and KeyDown key codes,
  type-to-select and modifier filtering.
- Real-X mode: `ClassicListBox real X input passed (14 steps)` in each of the
  final runs, under Openbox with xdotool: double-click a row (DoubleClick,
  ListIndex), Down (KeyDown 31 and native navigation), Return (KeyDown 13,
  no DoubleClick), typed `ap` (type-select), a consumed key, two header
  clicks (ascending then descending, indicator read from GTK), a cancelled
  header click (indicator restored), a header-edge drag on a resizable column
  (100 → 160 pt, read back natively), a click and a Ctrl+click in multiple
  mode (native set 2 rows, one Change each), a double-click in multiple mode,
  and a list resize that recomputes `100,*` from 300 to 200 pt.
- Mutation checks, each run in a temp copy, each failing as expected: no
  keyboard-activation filter (step 2: DoubleClick 2); no indicator restore
  after a cancelled header click (real-X step 7: indicator `1:0`); no
  multi-selection re-apply after reload; no initial header hide; percent
  widths ignored; no resize recomputation (real-X step 13). An unmodified copy passed the
  native-state mode.
- The driver waits 0.3 s before each action. Without it, GTK under Xvfb
  dropped a click sent right after the pointer motion, and sometimes a key
  sent right after other input. The probe's own assertions are unchanged.
- Six-target `--check` (x86_64/arm64 linux, darwin, windows): clean for the
  module and both tests.

Not run: macOS and Windows execution (type-checked only), arm64 Linux
execution, HiDPI/scaled displays, a real keyboard layout other than the Xvfb
default, and screen readers.

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
