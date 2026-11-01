---
title: "rbclassic \u00b7 ClassicCheckBoxMember"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicCheckBoxMember"]
dependencies: []
symbols: ["ClassicCheckBoxMember"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicCheckBoxMember

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicCheckBoxMember

`Public Class ClassicCheckBoxMember Inherits ClassicCheckBox Implements ClassicControlSetMember`

A CheckBox control-set member (API 1 Value/State from ClassicCheckBox).

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `Index` | `Integer` | Yes | No | — | API 1 `Index`: the position in the set, or -1 when not in a set. |

### ControlSetState

`Public Function ControlSetState() As ClassicControlSetState`

No parameters.

#### Returns

| Type |
| --- |
| `ClassicControlSetState` |

### ControlSetControl

`Public Function ControlSetControl() As UIControl`

No parameters.

#### Returns

| Type |
| --- |
| `UIControl` |

### ControlSetAttach

`Public Sub ControlSetAttach(host As Window)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `host` | `Window` | `ByVal` | Required |

Returns: no value.

### ControlSetAttachToView

`Public Sub ControlSetAttachToView(host As View)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `host` | `View` | `ByVal` | Required |

Returns: no value.

### Close

`Public Sub Close()`

API 1 `Close`: removes the control.

No parameters.

Returns: no value.
