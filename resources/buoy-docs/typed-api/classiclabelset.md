---
title: "rbclassic \u00b7 ClassicLabelSet"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicLabelSet"]
dependencies: []
symbols: ["ClassicLabelSet"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicLabelSet

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicLabelSet

`Public Class ClassicLabelSet Inherits ClassicControlSet`

A StaticText (Label) control set. Labels have no events.

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

`Public Function Item(index As Integer) As ClassicLabelMember`

The member with this index, or Nil.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `ClassicLabelMember` |

### Register

`Public Sub Register(member As ClassicLabelMember, index As Integer)`

Adds an already-placed label at an explicit index.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `member` | `ClassicLabelMember` | `ByVal` | Required |
| `index` | `Integer` | `ByVal` | Required |

Returns: no value.

### Attach

`Public Function Attach(member As ClassicLabelMember) As Integer`

Places a new label at LastIndex + 1 and raises Open.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `member` | `ClassicLabelMember` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### NewMember

`Public Function NewMember() As ClassicLabelMember`

API 1 `New Label1`: copies frame, Visible, Enabled and Text.

No parameters.

#### Returns

| Type |
| --- |
| `ClassicLabelMember` |
