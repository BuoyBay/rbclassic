---
title: "rbclassic \u00b7 ClassicSliderSet"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicSliderSet"]
dependencies: []
symbols: ["ClassicSliderSet"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicSliderSet

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicSliderSet

`Public Class ClassicSliderSet Inherits ClassicControlSet`

A Slider control set: `ValueChanged(index)`.

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

`Public Function Item(index As Integer) As ClassicSliderMember`

The member with this index, or Nil.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `ClassicSliderMember` |

### Register

`Public Sub Register(member As ClassicSliderMember, index As Integer)`

Adds an already-placed slider at an explicit index.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `member` | `ClassicSliderMember` | `ByVal` | Required |
| `index` | `Integer` | `ByVal` | Required |

Returns: no value.

### Attach

`Public Function Attach(member As ClassicSliderMember) As Integer`

Places a new slider at LastIndex + 1 and raises Open.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `member` | `ClassicSliderMember` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### NewMember

`Public Function NewMember() As ClassicSliderMember`

API 1 `New Slider1`: copies frame, Visible, Enabled, Minimum, Maximum and Value. The copied Value is set before the member joins the set, so it raises no ValueChanged.

No parameters.

#### Returns

| Type |
| --- |
| `ClassicSliderMember` |
