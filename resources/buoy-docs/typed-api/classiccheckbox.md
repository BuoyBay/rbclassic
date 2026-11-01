---
title: "rbclassic \u00b7 ClassicCheckBox"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicCheckBox"]
dependencies: []
symbols: ["ClassicCheckBox"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicCheckBox

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicCheckBox

`Public Class ClassicCheckBox Inherits DesktopCheckBox`

API 1 `CheckBox`: Boolean `Value`, tri-state `State`, and `Action`, which fires for user clicks and for programmatic changes of the state.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `Value` | `Boolean` | No | No | — | — |
| `State` | `ClassicCheckBox.CheckedStates` | No | No | — | API 1 `State As CheckBox.CheckedStates`. |
| `VisualState` | `DesktopCheckBox.VisualStates` | No | No | — | API 2 `VisualState`, same storage as State. |
