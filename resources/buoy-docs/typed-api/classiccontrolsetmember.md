---
title: "rbclassic \u00b7 ClassicControlSetMember"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicControlSetMember"]
dependencies: []
symbols: ["ClassicControlSetMember"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicControlSetMember

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicControlSetMember

`Public Interface ClassicControlSetMember`

Implemented by every ClassicXxxMember class. User code does not call these members; they let the set reach the concrete control type.

### ControlSetState

`Function ControlSetState() As ClassicControlSetState`

No parameters.

#### Returns

| Type |
| --- |
| `ClassicControlSetState` |

### ControlSetControl

`Function ControlSetControl() As UIControl`

No parameters.

#### Returns

| Type |
| --- |
| `UIControl` |

### ControlSetAttach

`Sub ControlSetAttach(host As Window)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `host` | `Window` | `ByVal` | Required |

Returns: no value.

### ControlSetAttachToView

`Sub ControlSetAttachToView(host As View)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `host` | `View` | `ByVal` | Required |

Returns: no value.
