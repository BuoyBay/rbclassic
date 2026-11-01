---
title: "rbclassic \u00b7 ClassicPushButton"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicPushButton"]
dependencies: []
symbols: ["ClassicPushButton"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicPushButton

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicPushButton

`Public Class ClassicPushButton Inherits Button`

API 1 `PushButton` with working `Default` (Return/Enter) and `Cancel` (Escape; macOS also Command-Period) keys. Action and Caption are Buoy's own.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `Default` | `Boolean` | No | No | — | API 1 `PushButton.Default`: Return and Enter press this button. |
| `Cancel` | `Boolean` | No | No | — | API 1 `PushButton.Cancel`: Escape presses this button. |

### Push

`Public Sub Push()`

API 1 `PushButton.Push`: presses the button and raises Action.

No parameters.

Returns: no value.

### Destructor

`Public Sub Destructor()`

No parameters.

Returns: no value.
