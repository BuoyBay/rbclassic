---
title: "rbclassic \u00b7 ClassicControlSet"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicControlSet"]
dependencies: []
symbols: ["ClassicControlSet"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicControlSet

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicControlSet

`Public Class ClassicControlSet`

Base class of the typed sets. Indexes are kept in ascending order and may be sparse. The set holds its members strongly; a member refers back to its set weakly, so dropping the set stops event routing without a cycle.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `Renumbering` | `ClassicControlSetRenumbering` | No | No | `ClassicControlSetRenumbering.Compact` | What Close/Remove does to the remaining indexes. Defaults to API 1's Control.Close behavior. |
| `Handler` | `ClassicControlSetHandler` | No | No | — | Optional handler called for every event after the typed event. |
| `NativeRemovalAvailable` | `Boolean` | Yes | Yes | — | True where Close/Remove can detach a native control (a removal can still raise for one control, for example before its window exists). |
| `ReparentAvailable` | `Boolean` | Yes | Yes | — | True where Reparent can move a member to another container. |
| `Count` | `Integer` | Yes | No | — | Number of members. |
| `LastIndex` | `Integer` | Yes | No | — | Highest index in use, or -1 for an empty set. |

### Constructor

`Public Sub Constructor(host As Window)`

Members created by NewMember/Attach are added to this window.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `host` | `Window` | `ByVal` | Required |

Returns: no value.

### Constructor (overload 2)

`Public Sub Constructor(host As View)`

Members created by NewMember/Attach are added to this container.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `host` | `View` | `ByVal` | Required |

Returns: no value.

### Indexes

`Public Function Indexes() As Array Of Integer`

The indexes in use, ascending (a copy).

No parameters.

#### Returns

| Type |
| --- |
| `Array Of Integer` |

### Contains

`Public Function Contains(index As Integer) As Boolean`

True when a member has this index.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### IndexOf

`Public Function IndexOf(control As UIControl) As Integer`

The member's index, or -1 when the control is not in this set.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `control` | `UIControl` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### Remove

`Public Sub Remove(index As Integer)`

API 1 `Close` for the member with this index.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

Returns: no value.

### RemoveMember

`Public Sub RemoveMember(member As ClassicControlSetMember)`

Raises Close, detaches the control natively and removes it. If it cannot be detached, raises UnsupportedOperationException before Close and nothing changes.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `member` | `ClassicControlSetMember` | `ByVal` | Required |

Returns: no value.

### Reparent

`Public Sub Reparent(member As ClassicControlSetMember, newHost As View)`

Moves a member natively into another container; its index is kept. Linux only (ReparentAvailable); elsewhere raises UnsupportedOperationException without changing anything.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `member` | `ClassicControlSetMember` | `ByVal` | Required |
| `newHost` | `View` | `ByVal` | Required |

Returns: no value.

### Reparent (overload 2)

`Public Sub Reparent(member As ClassicControlSetMember, newHost As Window)`

Moves a member natively into a window's content; see the View overload.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `member` | `ClassicControlSetMember` | `ByVal` | Required |
| `newHost` | `Window` | `ByVal` | Required |

Returns: no value.

### RouteEvent

`Public Sub RouteEvent(member As ClassicControlSetMember, eventName As String)`

Called by a member when its native event fires. Events of controls that were removed, or that belong to another set, are dropped.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `member` | `ClassicControlSetMember` | `ByVal` | Required |
| `eventName` | `String` | `ByVal` | Required |

Returns: no value.
