---
title: "rbclassic \u00b7 ClassicListColumn"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicListColumn"]
dependencies: []
symbols: ["ClassicListColumn"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicListColumn

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicListColumn

`Public Class ClassicListColumn`

API 1 `ListColumn`, as returned by ClassicListBox.Column(index).

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `WidthActual` | `Integer` | No | No | — | Width in points, read back from the native column. Assigning sets WidthExpression to that number of points. |
| `WidthExpression` | `String` | No | No | — | One ColumnWidths entry: points, "N%" or "*"/"N*". |
| `UserResizable` | `Boolean` | No | No | — | Whether the user can drag the column edge (native GTK resizable). |

### Constructor

`Public Sub Constructor(owner As ClassicListBox, index As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `owner` | `ClassicListBox` | `ByVal` | Required |
| `index` | `Integer` | `ByVal` | Required |

Returns: no value.
