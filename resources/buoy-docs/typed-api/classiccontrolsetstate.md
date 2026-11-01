---
title: "rbclassic \u00b7 ClassicControlSetState"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicControlSetState"]
dependencies: []
symbols: ["ClassicControlSetState"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicControlSetState

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicControlSetState

`Public Class ClassicControlSetState`

Bookkeeping every control-set member carries. Its members are Internal: only the set changes it.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `IsClosed` | `Boolean` | Yes | No | — | True once the control was removed with Close/Remove. A closed control is detached natively and can never rejoin a set. |
