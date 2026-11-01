---
title: "rbclassic \u00b7 ClassicDesktop functions"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: []
dependencies: []
symbols: ["AcceptFileDrop", "AcceptPictureDrop", "AcceptTextDrop", "ClassicAddEditMenuItems", "ClassicAddPage", "ClassicAddTab", "ClassicCloseWindowsForQuit", "ClassicDefaultButtonCount", "ClassicEditCommandEnabled", "ClassicExitCode", "ClassicHasFocus", "ClassicOpenDocuments", "ClassicPanelPageCount", "ClassicPerformEditCommand", "ClassicQuit", "ClassicRegisterPanelPage", "ClassicSetCallbackErrorHandler", "Copy", "Cut", "MaxHeight", "MaxWidth", "Maximize", "MinHeight", "MinWidth", "Minimize", "Paste", "Restore", "SelLength", "SelStart", "SelText", "SelectAll"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicDesktop functions

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicDesktop functions

### ClassicSetCallbackErrorHandler

`Public Sub ClassicSetCallbackErrorHandler(handler As ClassicCallbackErrorHandler)`

Installs (or, with Nil, removes) the handler for exceptions that escape event handlers ClassicDesktop raises from native callbacks.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `handler` | `ClassicCallbackErrorHandler` | `ByVal` | Required |

Returns: no value.

### Minimize

`Public Extension Sub Minimize(recv As Window)`

API 1 `Window.Minimize`: minimizes (macOS: miniaturizes) the window.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `Window` | `ByVal` | Required |

Returns: no value.

### Maximize

`Public Extension Sub Maximize(recv As Window)`

API 1 `Window.Maximize`: maximizes (macOS: zooms) the window. As in API 1, a window that is already maximized is restored to its prior state instead.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `Window` | `ByVal` | Required |

Returns: no value.

### Restore

`Public Extension Sub Restore(recv As Window)`

API 1 `Window.Restore`: un-minimizes a minimized window (back to its prior state, which may be maximized), otherwise un-maximizes a maximized one.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `Window` | `ByVal` | Required |

Returns: no value.

### MinWidth

`Public Extension Function MinWidth(recv As Window) As Integer`

REALbasic `Window.MinWidth`; same value as `MinimumWidth`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `Window` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### MinWidth (overload 2)

`Public Extension Sub MinWidth(recv As Window, Assigns value As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `Window` | `ByVal` | Required |
| `value` | `Integer` | `Assigns` | Required |

Returns: no value.

### MinHeight

`Public Extension Function MinHeight(recv As Window) As Integer`

REALbasic `Window.MinHeight`; same value as `MinimumHeight`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `Window` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### MinHeight (overload 2)

`Public Extension Sub MinHeight(recv As Window, Assigns value As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `Window` | `ByVal` | Required |
| `value` | `Integer` | `Assigns` | Required |

Returns: no value.

### MaxWidth

`Public Extension Function MaxWidth(recv As Window) As Integer`

REALbasic `Window.MaxWidth`; same value as `MaximumWidth`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `Window` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### MaxWidth (overload 2)

`Public Extension Sub MaxWidth(recv As Window, Assigns value As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `Window` | `ByVal` | Required |
| `value` | `Integer` | `Assigns` | Required |

Returns: no value.

### MaxHeight

`Public Extension Function MaxHeight(recv As Window) As Integer`

REALbasic `Window.MaxHeight`; same value as `MaximumHeight`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `Window` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### MaxHeight (overload 2)

`Public Extension Sub MaxHeight(recv As Window, Assigns value As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `Window` | `ByVal` | Required |
| `value` | `Integer` | `Assigns` | Required |

Returns: no value.

### AcceptTextDrop

`Public Extension Sub AcceptTextDrop(recv As UIControl)`

API 1 `RectControl.AcceptTextDrop` for a control implementing ClassicDropHandler.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `UIControl` | `ByVal` | Required |

Returns: no value.

### AcceptPictureDrop

`Public Extension Sub AcceptPictureDrop(recv As UIControl)`

API 1 `RectControl.AcceptPictureDrop`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `UIControl` | `ByVal` | Required |

Returns: no value.

### AcceptFileDrop

`Public Extension Sub AcceptFileDrop(recv As UIControl, type As FileType)`

API 1 `RectControl.AcceptFileDrop(fileType)`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `UIControl` | `ByVal` | Required |
| `type` | `FileType` | `ByVal` | Required |

Returns: no value.

### AcceptFileDrop (overload 2)

`Public Extension Sub AcceptFileDrop(recv As UIControl, typeName As String)`

API 1 `RectControl.AcceptFileDrop("special/any")`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `UIControl` | `ByVal` | Required |
| `typeName` | `String` | `ByVal` | Required |

Returns: no value.

### ClassicCloseWindowsForQuit

`Public Function ClassicCloseWindowsForQuit() As Boolean`

Runs API 1's quit sequence without quitting: each open window, in order, is asked CancelClose(True) (ClassicWindow) and then closed; a plain Buoy Window is closed and must be gone afterwards. Returns False as soon as one window refuses; windows already closed stay closed.

No parameters.

#### Returns

| Type |
| --- |
| `Boolean` |

### ClassicQuit

`Public Sub ClassicQuit(exitCode As Integer = 0)`

API 1 `Quit([exitCode])` with window vetoes honored (Buoy's Application.Quit consults no window). Returns without quitting when a window's CancelClose returns True; otherwise records `exitCode` (see ClassicExitCode) and quits on the next run-loop turn, after the windows' Close events.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `exitCode` | `Integer` | `ByVal` | `0` |

Returns: no value.

### ClassicExitCode

`Public Function ClassicExitCode() As Integer`

The exit code of the last ClassicQuit that went ahead (0 before any). Buoy sets a process exit code only through `Function Main() As Integer`, so return it after Application.Run: `Return ClassicExitCode()`.

No parameters.

#### Returns

| Type |
| --- |
| `Integer` |

### ClassicDefaultButtonCount

`Public Function ClassicDefaultButtonCount() As Integer`

Number of live ClassicPushButtons registered for Default/Cancel keys. The registry holds them weakly; this is exposed for lifetime diagnostics.

No parameters.

#### Returns

| Type |
| --- |
| `Integer` |

### ClassicAddPage

`Public Function ClassicAddPage(panel As PagePanel) As View`

Adds a page and remembers it so EmbedWithinPanel can find it by index (PagePanel has no page-by-index accessor).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `panel` | `PagePanel` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `View` |

### ClassicAddTab

`Public Function ClassicAddTab(panel As TabView, caption As String) As View`

Adds a tab and remembers its page for EmbedWithinPanel.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `panel` | `TabView` | `ByVal` | Required |
| `caption` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `View` |

### ClassicRegisterPanelPage

`Public Sub ClassicRegisterPanelPage(panel As UIControl, index As Integer, page As View)`

Registers a page created elsewhere (for example by a Window block's Page).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `panel` | `UIControl` | `ByVal` | Required |
| `index` | `Integer` | `ByVal` | Required |
| `page` | `View` | `ByVal` | Required |

Returns: no value.

### ClassicPanelPageCount

`Public Function ClassicPanelPageCount() As Integer`

Number of live registered panel pages (held weakly); for lifetime diagnostics.

No parameters.

#### Returns

| Type |
| --- |
| `Integer` |

### SelStart

`Public Extension Function SelStart(recv As TextField) As Integer`

API 1 `TextField.SelStart`: the insertion point / start of the selection.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `TextField` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### SelStart (overload 2)

`Public Extension Sub SelStart(recv As TextField, Assigns value As Integer)`

Setting SelStart moves the insertion point and collapses the selection.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `TextField` | `ByVal` | Required |
| `value` | `Integer` | `Assigns` | Required |

Returns: no value.

### SelLength

`Public Extension Function SelLength(recv As TextField) As Integer`

API 1 `TextField.SelLength`: selected character count, extending from SelStart.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `TextField` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### SelLength (overload 2)

`Public Extension Sub SelLength(recv As TextField, Assigns value As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `TextField` | `ByVal` | Required |
| `value` | `Integer` | `Assigns` | Required |

Returns: no value.

### SelText

`Public Extension Function SelText(recv As TextField) As String`

API 1 `TextField.SelText`: the selected text.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `TextField` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### SelText (overload 2)

`Public Extension Sub SelText(recv As TextField, Assigns value As String)`

Assigning SelText replaces the selection (inserting at the insertion point when nothing is selected) and leaves the insertion point after the text.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `TextField` | `ByVal` | Required |
| `value` | `String` | `Assigns` | Required |

Returns: no value.

### SelectAll

`Public Extension Sub SelectAll(recv As TextField)`

API 1 `TextField.SelectAll`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `TextField` | `ByVal` | Required |

Returns: no value.

### Copy

`Public Extension Sub Copy(recv As TextField)`

API 1 `TextField.Copy`: copies the selection to the clipboard (nothing when the selection is empty, or for a password field, which never exposes its text, as natively).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `TextField` | `ByVal` | Required |

Returns: no value.

### Paste

`Public Extension Sub Paste(recv As TextField)`

API 1 `TextField.Paste`: replaces the selection with the clipboard text. Does nothing for a read-only field or a clipboard without text.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `TextField` | `ByVal` | Required |

Returns: no value.

### SelStart (overload 3)

`Public Extension Function SelStart(recv As TextArea) As Integer`

API 1 `TextArea.SelStart`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `TextArea` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### SelStart (overload 4)

`Public Extension Sub SelStart(recv As TextArea, Assigns value As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `TextArea` | `ByVal` | Required |
| `value` | `Integer` | `Assigns` | Required |

Returns: no value.

### SelLength (overload 3)

`Public Extension Function SelLength(recv As TextArea) As Integer`

API 1 `TextArea.SelLength`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `TextArea` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### SelLength (overload 4)

`Public Extension Sub SelLength(recv As TextArea, Assigns value As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `TextArea` | `ByVal` | Required |
| `value` | `Integer` | `Assigns` | Required |

Returns: no value.

### SelText (overload 3)

`Public Extension Function SelText(recv As TextArea) As String`

API 1 `TextArea.SelText`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `TextArea` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### SelText (overload 4)

`Public Extension Sub SelText(recv As TextArea, Assigns value As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `TextArea` | `ByVal` | Required |
| `value` | `String` | `Assigns` | Required |

Returns: no value.

### SelectAll (overload 2)

`Public Extension Sub SelectAll(recv As TextArea)`

API 1 `TextArea.SelectAll`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `TextArea` | `ByVal` | Required |

Returns: no value.

### Copy (overload 2)

`Public Extension Sub Copy(recv As TextArea)`

API 1 `TextArea.Copy` (plain text; Buoy's TextArea has no styled text).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `TextArea` | `ByVal` | Required |

Returns: no value.

### Paste (overload 2)

`Public Extension Sub Paste(recv As TextArea)`

API 1 `TextArea.Paste`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `TextArea` | `ByVal` | Required |

Returns: no value.

### Cut

`Public Extension Sub Cut(recv As TextField)`

API 1 `TextField.Cut`: copies the selection to the clipboard and deletes it. Does nothing for a read-only or password field or an empty selection.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `TextField` | `ByVal` | Required |

Returns: no value.

### Cut (overload 2)

`Public Extension Sub Cut(recv As TextArea)`

API 1 `TextArea.Cut`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `recv` | `TextArea` | `ByVal` | Required |

Returns: no value.

### ClassicHasFocus

`Public Function ClassicHasFocus(control As UIControl) As Boolean`

True when keyboard focus is natively in this control (for a TextField or TextArea, in its editor). Buoy 0.72 has no Window.FocusedControl, so this is how converted EnableMenuItems/MenuSelected code finds the edit target.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `control` | `UIControl` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### ClassicEditCommandEnabled

`Public Function ClassicEditCommandEnabled(control As UIControl, command As String) As Boolean`

Whether the API 1 Edit menu command (`EditCut`, `EditCopy`, `EditPaste`, `EditClear`, `EditSelectAll`) applies to this TextField/TextArea now, from its native selection, read-only state and the clipboard. False for other controls and other command names (including `EditUndo`, which has no native availability query here).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `control` | `UIControl` | `ByVal` | Required |
| `command` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### ClassicPerformEditCommand

`Public Function ClassicPerformEditCommand(control As UIControl, command As String) As Boolean`

Performs an API 1 Edit menu command on a TextField/TextArea. Returns True when the command applied (so a MenuSelected handler can stop there), False when it does not apply to this control or is not available right now.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `control` | `UIControl` | `ByVal` | Required |
| `command` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### ClassicAddEditMenuItems

`Public Function ClassicAddEditMenuItems(base As MenuItem, control As UIControl) As Integer`

Appends API 1's standard text Edit items (Cut, Copy, Paste, Delete, a separator, Select All) to a ConstructContextualMenu `base`, tagged with the Edit command names and enabled from the control's current state. In ContextualMenuAction, `ClassicPerformEditCommand(Me, hitItem.Tag)` runs one. Returns the number of items appended (0 for a non-text control).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `base` | `MenuItem` | `ByVal` | Required |
| `control` | `UIControl` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### ClassicOpenDocuments

`Public Function ClassicOpenDocuments(args As Array Of String, handler As ClassicDocumentHandler) As Integer`

Routes the documents named on the launch command line (`Main`'s `args`, from args(1) on) to `handler.OpenDocument`, in order, as API 1 does at launch on Windows and Linux. Arguments that are not existing files (options, folders, missing paths) are skipped. Returns the number routed. Documents sent to an already running app, and macOS Finder open-document events, are not delivered (Buoy 0.72 has no hook for them).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `args` | `Array Of String` | `ByVal` | Required |
| `handler` | `ClassicDocumentHandler` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |
