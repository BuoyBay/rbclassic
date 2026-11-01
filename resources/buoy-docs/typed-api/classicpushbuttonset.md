---
title: "rbclassic \u00b7 ClassicPushButtonSet"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicPushButtonSet"]
dependencies: []
symbols: ["ClassicPushButtonSet"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicPushButtonSet

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicPushButtonSet

`Public Class ClassicPushButtonSet Inherits ClassicControlSet`

A PushButton control set: `Action(index)`.

### Constructor

`Public Sub Constructor(host As Window)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `host` | `Window` | `ByVal` | Required |

Returns: no value.

### Constructor (overload 2)

`Public Sub Constructor(host As View)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `host` | `View` | `ByVal` | Required |

Returns: no value.

### Item

`Public Function Item(index As Integer) As ClassicPushButtonMember`

The member with this index, or Nil.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `ClassicPushButtonMember` |

### Register

`Public Sub Register(member As ClassicPushButtonMember, index As Integer)`

Adds an already-placed button at an explicit index.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `member` | `ClassicPushButtonMember` | `ByVal` | Required |
| `index` | `Integer` | `ByVal` | Required |

Returns: no value.

### Attach

`Public Function Attach(member As ClassicPushButtonMember) As Integer`

Places a new button at LastIndex + 1 and raises Open.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `member` | `ClassicPushButtonMember` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### NewMember

`Public Function NewMember() As ClassicPushButtonMember`

API 1 `New PushButton1`: a copy of the lowest-index member (frame, Visible, Enabled, Caption) at LastIndex + 1. Default/Cancel are not copied: a window has one default and one cancel button.

No parameters.

#### Returns

| Type |
| --- |
| `ClassicPushButtonMember` |
