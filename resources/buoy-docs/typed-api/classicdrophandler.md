---
title: "rbclassic \u00b7 ClassicDropHandler"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicDropHandler"]
dependencies: []
symbols: ["ClassicDropHandler"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicDropHandler

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicDropHandler

`Public Interface ClassicDropHandler`

API 1 drop events for a control. A converted control subclass implements this interface (its former event handlers become these methods) and calls `AcceptTextDrop`/`AcceptPictureDrop`/`AcceptFileDrop` on itself. Returning True from DragEnter or DragOver rejects the drag, as in API 1.

### DragEnter

`Function DragEnter(obj As DragItem, action As Integer) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `obj` | `DragItem` | `ByVal` | Required |
| `action` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### DragOver

`Function DragOver(x As Integer, y As Integer, obj As DragItem, action As Integer) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `x` | `Integer` | `ByVal` | Required |
| `y` | `Integer` | `ByVal` | Required |
| `obj` | `DragItem` | `ByVal` | Required |
| `action` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### DragExit

`Sub DragExit(obj As DragItem, action As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `obj` | `DragItem` | `ByVal` | Required |
| `action` | `Integer` | `ByVal` | Required |

Returns: no value.

### DropObject

`Sub DropObject(obj As DragItem, action As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `obj` | `DragItem` | `ByVal` | Required |
| `action` | `Integer` | `ByVal` | Required |

Returns: no value.
