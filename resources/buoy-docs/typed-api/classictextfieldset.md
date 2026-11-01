---
title: "rbclassic \u00b7 ClassicTextFieldSet"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicTextFieldSet"]
dependencies: []
symbols: ["ClassicTextFieldSet"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicTextFieldSet

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicTextFieldSet

`Public Class ClassicTextFieldSet Inherits ClassicControlSet`

A TextField control set: `TextChange(index)`, `GotFocus(index)`, `LostFocus(index)`.

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

`Public Function Item(index As Integer) As ClassicTextFieldMember`

The member with this index, or Nil.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `ClassicTextFieldMember` |

### Register

`Public Sub Register(member As ClassicTextFieldMember, index As Integer)`

Adds an already-placed field at an explicit index.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `member` | `ClassicTextFieldMember` | `ByVal` | Required |
| `index` | `Integer` | `ByVal` | Required |

Returns: no value.

### Attach

`Public Function Attach(member As ClassicTextFieldMember) As Integer`

Places a new field at LastIndex + 1 and raises Open.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `member` | `ClassicTextFieldMember` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### NewMember

`Public Function NewMember() As ClassicTextFieldMember`

API 1 `New TextField1`: copies frame, Visible, Enabled, Text, Placeholder (API 1 CueText) and IsReadOnly (API 1 ReadOnly).

No parameters.

#### Returns

| Type |
| --- |
| `ClassicTextFieldMember` |
