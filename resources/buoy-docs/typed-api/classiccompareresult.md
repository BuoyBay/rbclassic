---
title: "rbclassic \u00b7 ClassicCompareResult"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicCompareResult"]
dependencies: []
symbols: ["ClassicCompareResult"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicCompareResult

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicCompareResult

`Public Class ClassicCompareResult`

Mutable result slot for ClassicListBox.CompareRows. Buoy events pass parameters by value, so API 1's `ByRef result As Integer` becomes `outcome As ClassicCompareResult` (`Result` is a Buoy keyword); rewrite `result = x` to `outcome.Value = x`.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `Value` | `Integer` | No | No | `0` | — |
