# ClassicDesktop: notes

Module: `modules/ClassicDesktop.bui`. It imports `Xojo` for
the shim foundation and `ClassicListNative`, which imports only `Xojo`, so there is no
cycle. That second import exists for the focused-list key routing below. Test:
`tests/classic_desktop_test.bui`, run on Linux by `tests/classic_desktop_verify.py`.

## Source rewrite

Buoy's own `Window` is a different class from API 1's, so converted code changes
its base class names. Member and event-handler names stay as they are in API 1.

| API 1 source | Converted |
|---|---|
| `Inherits Window` | `Inherits ClassicWindow` |
| `Inherits ContainerControl` | `Inherits ClassicContainerControl` |
| a `PushButton` that uses `Default`/`Cancel` | `ClassicPushButton` |
| control drop events (`DragEnter`/`DragOver`/`DragExit`/`DropObject`) | the control subclass `Implements ClassicDropHandler`; the handlers become those four methods |
| `Quit` / `Quit(code)` (when windows should be able to veto it) | `ClassicQuit()` / `ClassicQuit(code)` |
| `Sub Main` that should report `Quit(code)` | `Function Main(args As Array Of String) As Integer` … `Application.Run()` … `Return ClassicExitCode()` |
| `App.OpenDocument(item)` at launch | a `ClassicDocumentHandler`, plus `ClassicOpenDocuments(args, handler)` in `Main` |
| `EditCut.Enabled = TextField1.SelLength > 0` and similar in `EnableMenuItems` | `ClassicEditCommandEnabled(TextField1, "EditCut")` |
| the built-in Edit menu acting on the focused field | in `MenuSelected`: `If ClassicHasFocus(TextField1) Then Return ClassicPerformEditCommand(TextField1, item.Tag)` (items tagged with the API 1 names) |
| a text field's standard contextual menu | `ConstructContextualMenu`: `ClassicAddEditMenuItems(base, Me)`; `ContextualMenuAction`: `ClassicPerformEditCommand(Me, hitItem.Tag)` |
| `TextField.Cut` / `TextArea.Cut` | unchanged (extension) |
| `PagePanel.Append` / `TabPanel` tab creation, when containers are embedded later | `ClassicAddPage(panel)` / `ClassicAddTab(panel, caption)`, or `ClassicRegisterPanelPage` |

## Exports

Classes, interfaces and extensions come through a plain `Public Import ClassicDesktop`.

Globals need a selective import. The full list for the entry module:

```
Public Import ClassicDesktop.{ ClassicQuit, ClassicCloseWindowsForQuit, ClassicExitCode, ClassicAddPage, ClassicAddTab, ClassicRegisterPanelPage, ClassicSetCallbackErrorHandler, ClassicHasFocus, ClassicEditCommandEnabled, ClassicPerformEditCommand, ClassicAddEditMenuItems, ClassicOpenDocuments, ClassicDefaultButtonCount, ClassicPanelPageCount }
```

New this wave: `ClassicExitCode`, `ClassicSetCallbackErrorHandler`, `ClassicHasFocus`,
`ClassicEditCommandEnabled`, `ClassicPerformEditCommand`, `ClassicAddEditMenuItems`,
`ClassicOpenDocuments`, `ClassicDefaultButtonCount`, `ClassicPanelPageCount`.
`ClassicQuit` gained an optional `exitCode` parameter; existing `ClassicQuit()` calls
are unchanged. The two `…Count` functions are lifetime diagnostics.

Classes: `ClassicWindow`, `ClassicPushButton`, `ClassicContainerControl`,
`ClassicDropTarget` (new read-only `Control`), `ClassicDragAction`. Interfaces:
`ClassicDropHandler`, `ClassicCallbackErrorHandler` (new),
`ClassicDocumentHandler` (new).

Extension names, which can collide with other modules:

- `Window`: `Minimize`, `Maximize`, `Restore`, `MinWidth`, `MinHeight`, `MaxWidth`, `MaxHeight`.
- `UIControl`: `AcceptTextDrop`, `AcceptPictureDrop`, `AcceptFileDrop(FileType)`, `AcceptFileDrop(String)`.
- `TextField` and `TextArea`: `SelStart`, `SelLength`, `SelText` (each get and set), `SelectAll`, `Copy`, `Paste`, `Cut` (new).

No native libraries are staged. Every binding is a `Declare`/`Optional Declare` to
system libraries (GTK 4, user32/kernel32/imm32, AppKit/objc). The test needs only
the Xojo package and its bundled dependencies in `packages/`.

## What works, by platform

"Verified" means the behavior test ran on that platform. The **current** suite
(128 checks) was executed this wave only on Linux x86_64. The Windows and macOS
entries below come from the earlier 65-check suite, which predates this wave's
changes. The parent coordinates the foreign reruns.

| Feature | Linux | Windows | macOS |
|---|---|---|---|
| `Minimize` / `Maximize` (toggles when already maximized, as in API 1) / `Restore` | verified (GTK) | verified earlier (`ShowWindow`) | verified earlier (`miniaturize:`/`zoom:`) |
| `Minimize`/`Maximize`/`Restore` events | verified (GDK `notify::state`) | verified earlier (`WH_CALLWNDPROCRET` on `WM_SIZE`) | verified earlier (state re-read on Buoy's `Shown`/`Hidden`/`Resized`) |
| `Open`, `Close`, `CancelClose(False)`, `Resized` | verified | verified earlier | verified earlier |
| `Activate` | verified | verified earlier | SKIP (locked session) |
| `Resizing` vs `Resized` | `finished` flag | `WM_ENTERSIZEMOVE`/`WM_EXITSIZEMOVE` | `inLiveResize` |
| `MinWidth`/`MinHeight` | verified (enforced) | verified earlier (enforced) | verified earlier (`contentMinSize`) |
| `Default`: Return/Enter press the button | verified | verified earlier | key equivalent verified earlier; Return SKIP |
| `Cancel`: Escape presses the button | verified | verified earlier | key equivalent verified earlier; Escape SKIP |
| Return/Escape left to an IME composition | verified (GTK built-in input method, Ctrl+Shift+U) | implemented (`ImmGetCompositionStringW`), not run | AppKit's own key-equivalent handling, not tested |
| Return/Escape with a dropdown list open | verified (the dropdown keeps both keys) | implemented (`GetComboBoxInfo` + `CB_GETDROPPEDSTATE`), not run | not tested |
| `SelStart`/`SelLength`/`SelText`, `SelectAll`, `Copy`, `Paste` | verified | verified earlier | verified earlier |
| `Cut`, Edit commands, contextual Edit items, `ClassicHasFocus` | verified | implemented, not run | implemented, not run |
| `EmbedWithin`, `EmbedWithinPanel`; refused attempts leave the container unchanged | verified | embedding verified earlier; refusals not run | embedding verified earlier; refusals not run |
| control `Accept*Drop` with `ClassicDropHandler` | verified (`PerformDrop`) | verified earlier | verified earlier |
| registries do not keep released controls alive | verified | implemented, not run | implemented, not run |
| callback exceptions: handler, or rethrow to `UnhandledException` | verified | implemented, not run | not applicable (no module callbacks raise events) |
| `ClassicQuit` / `ClassicCloseWindowsForQuit` | verified | verified earlier | verified earlier |
| `ClassicQuit(code)` exit code through `Main` | verified (exit 7) | not delivered (see limitations) | implemented, not run |
| `ClassicOpenDocuments` | verified (synthetic arguments and a real launch argument) | implemented, not run | launch arguments only |

The arm64 Linux, x86_64 Windows and arm64 Windows builds of the current test
link. They were not run. Both darwin targets were checked with `--check` only;
this Linux host has no macOS SDK.

Details:

- **Positions are code points.** They index the control's own `Text`, so
  `Text.Substring(SelStart, SelLength) = SelText`. On Windows, `Text` holds CR LF, so a line end counts as two characters there.
- **Setting `SelStart` collapses the selection** to an insertion point. **`SelLength` extends from `SelStart`.** Values past the end clamp to the end, and negative values clamp to 0.
- **Assigning `SelText`** replaces the selection natively, so it is an undoable edit and raises `TextChanged`. Read-only controls ignore the assignment. macOS also honors the native shouldChange veto. The insertion point ends up after the inserted text.
- **`Copy`** does nothing when the selection is empty or the field is a password field. **`Cut`** also does nothing for a read-only field. **`Paste`** does nothing for a read-only control or a clipboard with no text. All use Buoy's `Clipboard`, with plain text only.
- **Password fields** never expose their text. `Copy`/`Cut` are no-ops and `EditCopy`/`EditCut` are disabled. `EditClear` stays available. This matches the native controls, which refuse to copy a masked field.
- **Edit commands.** The names are API 1's: `EditCut`, `EditCopy`, `EditPaste`, `EditClear`, `EditSelectAll`.
  - Enabled: Cut needs an editable, non-password field with a selection; Copy needs a non-password selection; Clear needs an editable selection; Paste needs an editable control and clipboard text; Select All needs non-empty text.
  - `ClassicPerformEditCommand` returns False when the command does not apply. That covers a non-text control, an unavailable command, an unknown name, and `EditUndo`.
- **`ClassicHasFocus`** reads native focus: GTK root focus (or a descendant), Win32 `GetFocus` (or a child), or the AppKit first responder. On macOS that includes the field editor whose delegate is the field.
- **`ClassicAddEditMenuItems`** appends Cut, Copy, Paste, Delete, a separator and Select All. It returns 5 for a text control and appends nothing (returns 0) otherwise. The native pop-up gesture itself is Buoy's `ConstructContextualMenu`; the test builds the menu item tree directly.
- **`Default` (Return/Enter).** A multi-line text view keeps Return, and so does a focused push button. A disabled, insensitive or unmapped button is not pressed. On Windows a disabled or invisible button is skipped, and keyboard focus stays where it was.
- **IME safety.** On Linux the key shortcut inspects the focused widget's key controller input-method context (`gtk_event_controller_key_get_im_context`, `gtk_im_context_get_preedit_string`). While preedit text exists, Return and Escape go to the input method, which commits or cancels the composition. On Windows a pending `GCS_COMPSTR` composition skips the hook. Keys the IME converts arrive as `VK_PROCESSKEY` and never match.
- **Focused ClassicListBox first (API 1 KeyDown order).** On Linux, while focus is inside an attached ClassicListBox, the Default/Cancel shortcut lets Return, keypad Enter and Escape through to the list, so its `KeyDown` runs first.
  - If `KeyDown` returns True, the key is consumed and no button is pressed.
  - If it declines, the list calls the handler that ClassicDesktop registered with `ClassicListNativeSetDeclinedKeyHandler`. That handler presses the window's mapped, sensitive Default (Return/Enter) or Cancel (Escape) button, and the list then does not activate the row natively.
  - The routing is an explicit interface in `ClassicListNative`: `ClassicDeclinedKeyHandler`, plus `ClassicListNativeOwnsKeys(focus)`. ClassicControls is unchanged.
  - On Windows and macOS the list bridge is not implemented, so ClassicListBox `KeyDown` never fires there and this ordering does not apply.
- **Open dropdowns.** On Linux, focus inside a `GtkPopover` keeps Return and Escape. In testing, the popover's own surface already kept both keys away from the window's capture shortcuts: the dropdown checks also pass with that guard removed, so the guard is defensive. On Windows, a combo box (the focused window or its parent) whose list is dropped keeps both keys.
- **Stale handles.** Windows checks `IsWindow` on the message target and on each button. Destroyed buttons are pruned from the weak registry. Linux shortcut callbacks carry a registry key, not an object pointer, so a callback for a destroyed button finds nothing.
- **Focused ListBox modifiers.** Declined Return/Enter/Escape reaches the Default/Cancel router only when no significant accelerator modifiers are held. The bridge uses [GTK's accelerator modifier mask](https://docs.gtk.org/gtk4/func.accelerator_get_default_mod_mask.html), which excludes Caps Lock. Ctrl/Shift+Return and Shift+Escape remain available to the focused control and do not press those buttons.
- **macOS keys.** An `NSButton` has one key equivalent, so asking for `Default` and `Cancel` on the same button raises `UnsupportedOperationException`, and the button keeps its previous state.
- **`CancelClose(appQuitting)`** gets `False` for a single window close and `True` during `ClassicQuit`/`ClassicCloseWindowsForQuit`.
- **Quit reentrancy (unchanged).** Closed/closing windows are skipped. A quit called from an in-flight CancelClose is deferred until its decision resolves, and a veto cancels that deferred request. The deferred request keeps its exit code. Nested quit calls during the quit sequence do not prompt again.
- **Quit sequence.** Windows are handled in `Application.Windows` order: each is asked, then closed. The first veto stops the sequence; windows already closed stay closed. `ClassicQuit` records its exit code only when the sequence completes, and calls `Application.Quit()` on the next run-loop turn.
- **Buoy's own events are still available.** ClassicWindow re-declares and re-raises Buoy's window events, so a subclass `Handle` does not replace the bridge.
- **Drop action codes** match API 1: Default 0, Copy 1, Move 2, Link 3. Returning True from `DragEnter` or `DragOver` rejects the drag. `DragExit` receives the item that entered.
- **`AcceptFileDrop(FileType)`** accepts a drop when any dropped file matches `FileType.Matches`. `AcceptFileDrop("special/any")` or `""` accepts any file. Any other name raises `InvalidArgumentException`.
- **`EmbedWithin`.** `Width` and `Height` default to the container's current size; `Left` and `Top` are added to the container's own `Left`/`Top`.
  - Refused before anything changes: embedding a second time (`UnsupportedOperationException`); a container that already has a parent, through `ParentWindow` or a native parent (`UnsupportedOperationException`); a width or height below -1 (`InvalidArgumentException`); an unknown panel page (`OutOfBoundsException`).
  - After `AddSubview`, the native parent chain is checked. If the native view is not inside the target, `UnsupportedOperationException` is raised. If `AddSubview` itself throws, geometry is restored and its original exception is rethrown.
  - This is not a full rollback. Geometry is restored and `IsEmbedded` stays False, but Buoy has no subview removal, so the completed `AddSubview` cannot be undone. The container stays added to the target on the Buoy side and may remain natively parented.
  - A mutation run without the precheck showed that this check also catches the parented case. GTK left the view in its old parent there, so geometry restore was the only change needed. A real failure after attachment is not claimed to be atomic.
- **Lifetimes.** Drop targets hold their control weakly; when the handler is the control itself, it is reached through the same weak reference. Default/Cancel buttons and panel pages are registered weakly, and entries are pruned. After a released control is destroyed, its drop target refuses every drag. The Linux window-state table still holds a `ClassicWindow` strongly from `Opened` until `Closed`, which is the window's own lifetime.
- **Callback exceptions.**
  - Covered: Minimize/Maximize/Restore events, which ClassicDesktop raises from GDK `notify::state` or `WH_CALLWNDPROCRET`. They are caught in the callback with no native frames in between.
  - A handler set with `ClassicSetCallbackErrorHandler` gets `(e, origin)`; returning True handles the exception.
  - Otherwise the exception is printed with its origin on stderr and rethrown unchanged from a Timer tick on the next run-loop turn. Buoy's normal uncaught path then applies: `Application.UnhandledException`, then abort. If the handler itself throws, that exception is the one rethrown.
- **Action exceptions from Default/Cancel keys are not caught.** That covers keys pressed directly and keys a focused list declined. `PerformClick` raises Action through the native button signal, and catching there would unwind through the GLib emission and crash (CWD-001). Such an exception therefore takes Buoy's uncaught path in place, exactly as for a mouse click; the `--action-abort` scenario verifies this.
- **Runtime boundary: an enclosing Try around `ShowModally` (CWD-001).** An exception from any runtime-dispatched handler inside a modal loop can be caught by a user Try around `ShowModally`, unwinding across GTK's nested main loop. Plain Buoy code is enough to trigger it, with no RBClassic involved:
  - a plain `Button` clicked with real input then segfaults the process;
  - a `Timer` was caught without a crash in the observed runs;
  - the independent review also reported hangs and traps, which were not reproduced here.

  This is a Buoy runtime defect, and ClassicDesktop does not and cannot fix it. Do not rely on catching event-handler exceptions across `ShowModally`; handle them inside the handler.
- **Documents.** `ClassicOpenDocuments(args, handler)` routes existing, non-folder files from `args(1)` on, in order. Options, folders and missing paths are skipped. It returns the number routed.

## Limitations: explicit errors or not provided

- **Window-level drops.** A Buoy `Window` is not a drop target, and `Window.SetContentView` is missing in 0.72 (CWD-002). `Accept*Drop` on a Window raises `UnsupportedOperationException`; accept the drop on a control.
- **Accept\*Drop on a plain control** that does not implement `ClassicDropHandler` raises `UnsupportedOperationException`.
- **Selection on an unfocused macOS TextField** raises `UnsupportedOperationException` until the field has focus.
- **No `Window.FocusedControl`/`ClearFocus`** in the 0.72 compiler, although `window.md` documents them (CWD-002). Buoy has no subview enumeration either, so there is no "find the focused control" helper. Converted code asks `ClassicHasFocus` of its own text controls.
- **`EditUndo`** is not routed. GTK's `GtkText` has no public can-undo query, so availability could not be reported truthfully.
- **Window events not bridged:** the window's `ConstructContextualMenu`/`ContextualMenuAction` and `EnableMenuItems` (GTK never raised the window-level `ConstructContextualMenu` or `MenuNeedsUpdate`); `KeyDown`/`KeyUp`, `Mouse*`, `Moved`, `Paint`, `ContentsChanged`, `ScaleFactorChanged()`.
- **`ContainerControl.Close`.** Buoy has no subview removal; hide the container with `Visible = False`.
- **Embedding precheck on Windows.** A child HWND exists only once its container is attached, so a container inside an unattached view cannot be detected there. The post-attach check also cannot verify a buffered child, so such cases count as attached.
- **App lifecycle:**
  - Buoy's `Application.Quit()` consults no window. A native quit command (Cmd-Q, or a menu item wired to `Application.Quit`) bypasses the veto sequence; only `ClassicQuit` runs it.
  - There is no `App.CancelClose` hook, and `AllowAutoQuit = False` is not provided. The Linux bridge quits its main loop directly on the last close, so no GTK application hold can keep it running. No hidden window is used to fake it.
  - On GTK, closing the first-created window ends `Application.Run` while other windows are open (BUI-104). The link-time `libraries/gtklifecycle` guard corrects this for executables that link it. ClassicDesktop is a package module and cannot link it.
  - **Exit codes.** `ClassicExitCode` only reaches the OS through `Function Main … Return ClassicExitCode()`. On Windows the process ends when the last window closes, before `Run` returns, so the code is not delivered there.
  - **Documents.** Documents sent to an already running instance, and macOS Finder open-document events (`application:openURLs:`), are not delivered; Buoy 0.72 has no hook for them.
  - On macOS, a plain (non-Classic) Buoy `Window` still listed after `Close()` counts as a veto, because AppKit finishes the close on a later run-loop turn. Use `ClassicWindow` for every window.
- **Resizing on Linux.** GTK reports a programmatic resize as unfinished and then finished, so `Resizing` also fires before `Resized` for code-driven size changes there.
- **MinWidth enforcement differs.** The runtime clamps a programmatic `Width` below `MinWidth` on Linux and Windows. macOS, like real Xojo, limits only user resizing.
- **Untested guard.** `Minimize`/`Maximize`/`Restore` on a window with no native handle raises `UnsupportedOperationException`. No platform produced such a window in testing.

## Runtime and compiler findings (Buoy 0.72.0) for core work

1. A plain `Declare … Lib "libgtk-4.so.1"` fails to link on Linux; `Optional Declare` works. A libc symbol aliased through the GTK library (`strlen`) also forces link-time resolution, so this module avoids it.
2. The bundled Windows import libraries lack `IsZoomed`, `SetWindowsHookExW` and `CallNextHookEx` (BUI-013). All Win32 calls here, including the new `imm32` ones, are `Optional Declare`.
3. `Optional Declare`s that alias the same export with different signatures fail LLVM verification (BUI-010).
4. `Math.Min`/`Math.Max` on `Int32` emits an invalid `fptosi` (BUI-012).
5. A parameter named `text` shadows the `Text` namespace. `result` and `path` are reserved as local names.
6. On GTK, closing the first-created window ends `Application.Run` (BUI-104).
7. A subclass `Handle` silently replaces the base class's handler for the same event.
8. Windows: `Resized` reports `finished=False` for programmatic, maximize and restore resizes; nothing fires on minimize; `Activated` waits until the window is in the foreground.
9. macOS: `Window.Close()` completes on a later run-loop turn.
10. **CWD-001 (new candidate).** An exception from a runtime-dispatched event handler is caught by an enclosing Try across native GTK frames, and the process then crashes. Two triggers: `PerformClick`, and a plain `Button` click inside `ShowModally`. With no enclosing Try, both controls abort cleanly through `UnhandledException`.
11. **CWD-002 (new candidate).** `Window.FocusedControl`, `ClearFocus` and `SetContentView` are documented but missing. The probe reports four errors: the three members plus a follow-on assignment error.
12. Adding a view that already has a parent with `AddSubview` does not throw. GTK reports `gtk_fixed_put: assertion … failed`, and the view stays where it was.

Candidate repros and evidence: `upstream-issues/classic-wave2-desktop/`. The parent
reconciles the central index. Independent review is pending.

Core gaps worth adding: `Window` as a drop target and `SetContentView`; window-level
`ConstructContextualMenu`/`MenuNeedsUpdate` on GTK; an app-level quit veto,
quit-on-last-window flag and exit code; open-document events; native window
minimized/maximized events; selection APIs on `TextField`/`TextArea`;
`FocusedControl` and subview enumeration; a page-by-index accessor on
`PagePanel`/`TabView`; subview removal; event dispatch that confines exceptions at
native signal boundaries.

## Checks

- `buoy ClassicDesktop.bui --check --diagnostic-format json`: exit 0 and no errors on all six targets (x86_64/arm64 × linux/darwin/windows). The only warning comes from the installed Xojo package (`XojoDesktop.bui:160`).
- `tests/classic_desktop_test.bui`: same result on all six targets. Builds link for x86_64-linux, arm64-linux, x86_64-windows and arm64-windows. Darwin cannot link on this host.
- Linux behavior run, from an isolated temp directory holding the module, test, verifier and `packages/` (the installed Xojo-1.0.0 and its dependency `.buipkg`s):

  ```
  buoy classic_desktop_test.bui -o test
  docker run --rm --network none --entrypoint sh -v DIR:/w -w /w buoy:0.72.0-gui \
    -c "dbus-run-session -- xvfb-run -a -s '-screen 0 1280x1024x24' python3 classic_desktop_verify.py ./test"
  ```

  The verifier starts Openbox and pins `GTK_IM_MODULE=gtk-im-context-simple`. It runs three processes:
  1. The contract with a real launch document argument. It must print `PASSED: 128 checks` and exit 7.
  2. `--callback-abort`: the Minimize exception reaches `UnhandledException` through the deferred rethrow.
  3. `--action-abort`: the Action exception reaches `UnhandledException` in place, with no crash and no GLib emission error.

  Result: all three passed. All 81 original checks are retained among the 128; the five list-ordering checks are new since the 123-check run.
- Mutation controls, run on Linux:
  - Removing the focused-list pass-through fails all five list-ordering checks; removing only the declined-key handler fails the three "declined" checks.
  - Removing the IME and popover guards fails exactly the two IME checks; the dropdown checks still pass (see "Open dropdowns").
  - Making the three registries strong fails all five lifetime checks.
  - Removing the parent precheck is still caught by the post-attach verification and rollback.
- `ClassicListNative.bui` was checked clean on all six targets. Its own suites were rerun with the gtklifecycle guard linked, as the parent's runner does:
  - `classic_list_native_verify.py` passed (14 real-input steps);
  - `classic_controls_test` passed.

  Without the guard, the original and the modified ListNative fail identically (the BUI-007/BUI-103 lifecycle issue).
- Not done this wave: Windows and macOS execution of the current suite, no GUI work on the shared desktops. Independent review with `buoy-code-reviewer` was not run by this sub-agent, because no subagents were allowed. The parent owns that review.
