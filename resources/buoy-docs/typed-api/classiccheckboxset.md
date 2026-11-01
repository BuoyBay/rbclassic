---
title: "rbclassic \u00b7 ClassicCheckBoxSet"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicCheckBoxSet"]
dependencies: []
symbols: ["ClassicCheckBoxSet"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicCheckBoxSet

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicCheckBoxSet

`Public Class ClassicCheckBoxSet Inherits ClassicControlSet`

A CheckBox control set: `Action(index)`.

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

`Public Function Item(index As Integer) As ClassicCheckBoxMember`

The member with this index, or Nil.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `ClassicCheckBoxMember` |

### Register

`Public Sub Register(member As ClassicCheckBoxMember, index As Integer)`

Adds an already-placed checkbox at an explicit index.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `member` | `ClassicCheckBoxMember` | `ByVal` | Required |
| `index` | `Integer` | `ByVal` | Required |

Returns: no value.

### Attach

`Public Function Attach(member As ClassicCheckBoxMember) As Integer`

Places a new checkbox at LastIndex + 1 and raises Open.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `member` | `ClassicCheckBoxMember` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### NewMember

`Public Function NewMember() As ClassicCheckBoxMember`

API 1 `New CheckBox1`: copies frame, Visible, Enabled, Caption and State from the lowest-index member. Setting the copied State raises no Action: the member is not in the set yet.

No parameters.

#### Returns

| Type |
| --- |
| `ClassicCheckBoxMember` |
