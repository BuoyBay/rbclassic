---
title: "rbclassic \u00b7 ClassicCanvas"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicCanvas"]
dependencies: []
symbols: ["ClassicCanvas"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicCanvas

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicCanvas

`Public Class ClassicCanvas Inherits Canvas`

API 1 `Canvas` event bridge. Subclass it instead of `Canvas` and handle:  Paint(g As ClassicGraphics, areas As Array Of Rect) MouseDown(x As Integer, y As Integer) As Boolean MouseDrag(x As Integer, y As Integer)   ' only after MouseDown returned True MouseUp(x As Integer, y As Integer)     ' only after MouseDown returned True MouseMove(x As Integer, y As Integer) MouseEnter() / MouseExit()  `areas` is always empty, which legacy defines as "redraw the whole canvas". `Backdrop` is drawn at its natural size at (0, 0) before `Paint`. Coordinates are local and rounded down to Integer. Repaints are always deferred: there is no synchronous `Refresh`/`RefreshRect`; use `Invalidate`.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `Backdrop` | `ClassicPicture` | No | No | — | API 1 `Canvas.Backdrop` (Nil for none); assigning schedules a repaint. Wrap a plain Picture with `New ClassicPicture(pic)`. |

### Invalidate

`Public Sub Invalidate(eraseBackground As Boolean)`

API 1 `Invalidate(eraseBackground)` — schedules a full repaint. `eraseBackground` is accepted and has no effect (legacy honours it only on Windows).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `eraseBackground` | `Boolean` | `ByVal` | Required |

Returns: no value.

### Invalidate (overload 2)

`Public Sub Invalidate(x As Integer, y As Integer, width As Integer, height As Integer, eraseBackground As Boolean = True)`

API 1 `Invalidate(x, y, width, height, [eraseBackground])` — schedules a repaint of the rectangle.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `x` | `Integer` | `ByVal` | Required |
| `y` | `Integer` | `ByVal` | Required |
| `width` | `Integer` | `ByVal` | Required |
| `height` | `Integer` | `ByVal` | Required |
| `eraseBackground` | `Boolean` | `ByVal` | `True` |

Returns: no value.
