---
title: "rbclassic \u00b7 ClassicControlSetRenumbering"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicControlSetRenumbering"]
dependencies: []
symbols: ["ClassicControlSetRenumbering"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicControlSetRenumbering

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicControlSetRenumbering

`Public Enum ClassicControlSetRenumbering As Integer`

How indexes change when a member is removed.

### Values

| Name | Type | Value / Default | Description |
| --- | --- | --- | --- |
| `Compact` | `ClassicControlSetRenumbering` | `0` | API 1 `Control.Close`: "the indexes for the remaining controls will shift downward so that the indexes start with zero and are consecutive." |
| `KeepHoles` | `ClassicControlSetRenumbering` | `1` | The legacy user guide's control-set topic: removing a member leaves a hole, and that index reads as Nil. |
