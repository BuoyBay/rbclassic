---
title: "rbclassic \u00b7 ClassicDragAction"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicDragAction"]
dependencies: []
symbols: ["ClassicDragAction"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicDragAction

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicDragAction

`Public Class ClassicDragAction`

API 1 `DragItem.DragActionDefault`/`Copy`/`Move`/`Link` codes.

### Constants

| Name | Type | Value / Default | Description |
| --- | --- | --- | --- |
| `DragActionDefault` | `Integer` | `0` | — |
| `DragActionCopy` | `Integer` | `1` | — |
| `DragActionMove` | `Integer` | `2` | — |
| `DragActionLink` | `Integer` | `3` | — |

### FromAction

`Public Shared Function FromAction(action As DragAction) As Integer`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `action` | `DragAction` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |
