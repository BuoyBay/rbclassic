---
title: "rbclassic \u00b7 ClassicTimer"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicTimer"]
dependencies: []
symbols: ["ClassicTimer"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicTimer

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicTimer

`Public Class ClassicTimer Inherits Timer`

Rewrite Timer declarations to ClassicTimer for observed one-shot completion. Configure through Mode/RunMode/Enabled; direct Start/Stop bypass the shim.

### NotifyTick

`Public Overrides Sub NotifyTick()`

No parameters.

Returns: no value.
