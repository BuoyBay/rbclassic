---
title: "rbclassic \u00b7 ClassicPrintDestination"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicPrintDestination"]
dependencies: []
symbols: ["ClassicPrintDestination"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicPrintDestination

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicPrintDestination

`Public Enum ClassicPrintDestination As Integer`

Destination kinds: PDF only (no print system), CUPS queue, GTK printer.

### Values

| Name | Type | Value / Default | Description |
| --- | --- | --- | --- |
| `PDF` | `ClassicPrintDestination` | `0` | — |
| `CupsQueue` | `ClassicPrintDestination` | `1` | — |
| `GtkPrinter` | `ClassicPrintDestination` | `2` | — |
