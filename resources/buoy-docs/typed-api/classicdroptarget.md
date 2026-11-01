---
title: "rbclassic \u00b7 ClassicDropTarget"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicDropTarget"]
dependencies: []
symbols: ["ClassicDropTarget"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicDropTarget

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicDropTarget

`Public Class ClassicDropTarget Implements IDropTarget`

The IDropTarget behind the API 1 Accept*Drop methods. Owns the accepted kinds, the file-type filter and the drag in progress (Buoy's DragLeft has no payload; API 1's DragExit receives the item that entered). The control is held weakly, so a target never keeps its control alive; when the handler is the control itself it is looked up through that weak reference. Once the control is gone every drag is refused.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `Control` | `UIControl` | Yes | No | — | The control this target was created for, or Nil once it has been destroyed. |

### Constructor

`Public Sub Constructor(control As UIControl, handler As ClassicDropHandler)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `control` | `UIControl` | `ByVal` | Required |
| `handler` | `ClassicDropHandler` | `ByVal` | Required |

Returns: no value.

### AcceptTextDrop

`Public Sub AcceptTextDrop()`

No parameters.

Returns: no value.

### AcceptPictureDrop

`Public Sub AcceptPictureDrop()`

No parameters.

Returns: no value.

### AcceptFileDrop

`Public Sub AcceptFileDrop(type As FileType)`

Accepts files whose path matches `type` (`FileType.Matches`).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `type` | `FileType` | `ByVal` | Required |

Returns: no value.

### AcceptFileDrop (overload 2)

`Public Sub AcceptFileDrop(typeName As String)`

Accepts any file for `"special/any"` (or `""`). Other names refer to IDE FileTypeSet entries that do not exist here; pass the FileType instead.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `typeName` | `String` | `ByVal` | Required |

Returns: no value.

### Accepts

`Public Function Accepts(payload As DragItem) As Boolean`

True when the payload carries a representation this target accepts.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `payload` | `DragItem` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### DragEntered

`Public Overrides Function DragEntered(payload As DragItem, requested As DragAction) As DragAction`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `payload` | `DragItem` | `ByVal` | Required |
| `requested` | `DragAction` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `DragAction` |

### DragOver

`Public Overrides Function DragOver(payload As DragItem, requested As DragAction, pt As Point) As DragAction`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `payload` | `DragItem` | `ByVal` | Required |
| `requested` | `DragAction` | `ByVal` | Required |
| `pt` | `Point` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `DragAction` |

### DragLeft

`Public Overrides Sub DragLeft()`

No parameters.

Returns: no value.

### DragDropped

`Public Overrides Function DragDropped(payload As DragItem, action As DragAction, pt As Point) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `payload` | `DragItem` | `ByVal` | Required |
| `action` | `DragAction` | `ByVal` | Required |
| `pt` | `Point` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |
