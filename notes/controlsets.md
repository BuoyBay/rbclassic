# ClassicControlSets: API 1 control sets

Module: `modules/ClassicControlSets.bui`. It imports `Xojo` and the sibling
modules `ClassicDesktop` (for `ClassicPushButton`) and `ClassicControls` (for
`ClassicCheckBox`). It never imports `rbclassic`.

## Exports

The module exports only types, so `Public Import ClassicControlSets` is enough.
No selective `.{ … }` line is needed. The test names the
`ClassicControlSetRenumbering` enum, and a full-entry check names the
`ClassicControlSetHandler` closure type, both through that plain import.

- **Sets:** `ClassicControlSet` (the base class), plus `ClassicPushButtonSet`, `ClassicCheckBoxSet`, `ClassicTextFieldSet`, `ClassicLabelSet` and `ClassicSliderSet`.
- **Members:** `ClassicPushButtonMember` (over `ClassicPushButton`), `ClassicCheckBoxMember` (over `ClassicCheckBox`), `ClassicTextFieldMember`, `ClassicLabelMember` and `ClassicSliderMember`.
- **Support types:** the `ClassicControlSetMember` interface, `ClassicControlSetState`, the `ClassicControlSetRenumbering` enum (`Compact`, `KeepHoles`) and the `ClassicControlSetHandler` closure type.

Possible name collisions: each member class adds `Index`, `Close()` and the
`ControlSet*` interface methods. `ClassicTextFieldMember` also shadows `Text`.

The entry module uses `Public Import ClassicControlSets`.

## Source rewrite

| API 1 | Converted |
|---|---|
| Controls `PushButton1` with Index 0, 2, 5 | `ClassicPushButtonMember` controls placed as usual, then `set.Register(member, index)` for each |
| `PushButton1(i)` | `set.Item(i)` (Nil when the index is missing) |
| `Sub Action(index As Integer)` on the control set | `Handle Action(index As Integer)` in a `ClassicPushButtonSet` subclass, or `set.Handler = Lambda (eventName As String, index As Integer) … End Lambda` |
| `PushButton1(i).Index` | `member.Index` (-1 outside a set) |
| `Dim b As New PushButton1` | `Dim b As ClassicPushButtonMember = set.NewMember()` |
| `b.Close` | `b.Close()` or `set.Remove(i)` |
| `TextChange(index)`, `GotFocus(index)`, `LostFocus(index)` | the same names on `ClassicTextFieldSet` |
| CheckBox `Action(index)`, Slider `ValueChanged(index)` | the same names on `ClassicCheckBoxSet` / `ClassicSliderSet` |
| `Open(index)` / `Close(index)` for a set member | the set's `Open` / `Close` events |

The legacy `New ControlSetName` syntax is not converted automatically. No
converter support exists for it, so the call site has to be rewritten to
`NewMember()` by hand.

## Behavior

The sources are the Xojo `Control` reference, deprecated API 1
(documentation.xojo.com/api/deprecated/control), and the user guide's "Sharing
event handlers with Control Sets" topic.

- **Indexes.** Indexes are kept in ascending order and may be sparse. Registering out of order is fine.
  - `Count` is the number of members. `LastIndex` is the highest index, or -1 for an empty set. `Indexes()` returns a copy.
  - `Contains(i)` and `IndexOf(control)` find a member. `IndexOf` compares identity.
  - A missing index reads as Nil, as in the user guide.
- **Register errors.** Each of these raises, and the set is unchanged afterwards:
  - a duplicate index: `InvalidArgumentException`
  - a negative index: `OutOfBoundsException`
  - the same member registered twice: `InvalidArgumentException`
  - a member of another set: `InvalidArgumentException`
  - a closed control: `UnsupportedOperationException`
- **Shared event dispatch.** Every native event of a member is routed to its set with the member's current index. The typed event runs first, then the optional `Handler` closure, which receives the API 1 event name.
  - A control outside the set routes nothing.
  - Events of a removed member are dropped. So are events of a member whose set has been destroyed.
- **NewMember** (API 1 `New PushButton1`). It needs a template, the lowest-index member; an empty set raises `UnsupportedOperationException`. The new control goes into the set's host, the Window or View given to the constructor, at `LastIndex + 1`. The `Index` page says each new instance increments the index. `Open(index)` is raised once.
  - Every type copies the frame, `Visible` and `Enabled`.
  - PushButton copies `Caption`. `Default` and `Cancel` are not copied, because a window has one default and one cancel button.
  - CheckBox copies `Caption` and `State`. TextField copies `Text`, `Placeholder` and `IsReadOnly`. Label copies `Text`. Slider copies `Minimum`, `Maximum` and `Value`.
  - The copied values are set before the member joins the set, so they raise no events.
  - `Attach(member)` places a new control you built yourself. It refuses a control that is already placed.
- **Close / Remove.** The set first checks that the control can be detached natively. If it cannot, it raises `UnsupportedOperationException` before raising `Close`, and nothing changes. An example is a control that was never placed.
  - If it can, the set raises `Close(index)` while the member is still in the set. It then detaches the native control, removes the member, and marks it closed (`ControlSetState().IsClosed`; `Index` becomes -1).
  - If the `Close` handler throws, the removal is cancelled, the guard is reset, and a later removal works. The guard is reset explicitly in `Catch`, because of BUI-015.
  - A second `Close` does nothing. A closed control cannot rejoin a set.
- **Renumbering.** The two Xojo sources disagree. The API 1 `Control.Close` page says the remaining indexes "shift downward so that the indexes start with zero and are consecutive". The user guide topic says a removed index leaves a hole that reads as Nil. Both behaviors are implemented and tested:
  - `Renumbering = Compact` is the default and follows `Control.Close`.
  - `Renumbering = KeepHoles` follows the user guide.
- **Native detach.**
  - Linux: take a GObject reference, then call `gtk_widget_unparent`. The control's native parent must be a GtkFixed, which is what a View or Window content area is.
  - Windows: `ShowWindow(SW_HIDE)`, then `SetParent(HWND_MESSAGE)`.
  - macOS: `-retain`, then `removeFromSuperview`.
  - The extra native reference is kept for the life of the process, because the Buoy runtime still owns the control object (see "Boundaries").
- **Reparent(member, View/Window)** is Linux only (`ClassicControlSet.ReparentAvailable`). It detaches the control natively and adds it to the new host. The member keeps its index and its `ParentWindow`. Elsewhere it raises `UnsupportedOperationException` before changing anything.
- **Lifetime.** A set holds its members strongly. Each member points back to its set weakly. A set nobody references is destroyed; its members stay on screen and route nothing. `Close()` on a member without a set still detaches it.
- **TextChange.** API 1 raises `TextChange` for a programmatic change too. Buoy's `TextChanged` fires only for edits, which is documented in `ui/textfield.md`. So `ClassicTextFieldMember` shadows `Text` and routes `TextChange` once, when an assignment changes the text and the native event did not fire. Assigning through a plain `TextField` reference raises nothing.

## Boundaries

Independent Opus review found a case-only Text assignment was discarded; the
setter now compares case-sensitively and has a regression. Template clones now
copy all four Lock flags. Successful Linux reparenting releases the temporary
GObject reference used during detach; removed controls still retain theirs.
The template's frame is relative to its own container: use a template in the
set's host to avoid interpreting coordinates from a different container.
 Lock flags are copied after native
attachment and before Open, since attachment resets their earlier values.
The default Compact policy remains an explicit API 1 choice; callers retaining
indexes should select KeepHoles deliberately. The conflicting guide contracts
do not establish one universal renumbering rule.

- **Windows and macOS removal is not verified.** It is implemented and passes the compiler checks for all six targets, but it has not been run.
  - On Windows a control has no HWND until its window exists natively. Removing it before that raises `UnsupportedOperationException` ("show its window first").
  - Reparenting is not offered on either platform.
- **Removed controls are not freed.** Buoy has no public removal API (CS-001), so the runtime keeps the control object in its old container's records. The native handle keeps one extra reference until the process exits, and on Windows the control lives on as a message-only window.
- **A closed control must not be used again.** Moving or resizing it makes GTK report `gtk_fixed_move` CRITICALs, as reproduced in CS-001.
- **Attach can miss an existing placement.** It detects controls it placed itself, and controls whose `ParentWindow` is known. It cannot detect a control placed inside a View that has not been added to a window yet.
- **Member types.** Members exist for PushButton, CheckBox, TextField, Label (StaticText) and Slider. Other control types, such as RadioButton, ListBox, PopupMenu and Canvas, have no member class yet.
- **Not modeled:** API 1 per-control events beyond those listed, IDE-assigned names, and the design-time `Open` for registered members (only members created at run time raise `Open`).
- **No generic set.** Buoy's `AddSubview` is overloaded per concrete control type, so each member class implements the attach itself.

## Roadmap

This completes the core of the ROADMAP item "Dynamic control sets with indexed
events, removal and ownership", within the boundaries above. Remaining:

- native Windows/macOS execution
- more member types
- freeing removed controls, which needs a core removal API (CS-001)
- reparenting outside Linux
- "complete container reparenting/focus/menu behavior"
