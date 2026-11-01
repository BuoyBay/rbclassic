---
title: "rbclassic \u00b7 ClassicContainerControl"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicContainerControl"]
dependencies: []
symbols: ["ClassicContainerControl"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicContainerControl

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicContainerControl

`Public Class ClassicContainerControl Inherits View`

API 1 `ContainerControl`. Width/Height default to the container's own size (its design size); Left/Top are added to the container's own Left/Top. A container can be embedded once.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `Left` | `Integer` | No | No | — | API 1 `ContainerControl.Left` (Buoy's View.X). |
| `Top` | `Integer` | No | No | — | API 1 `ContainerControl.Top` (Buoy's View.Y). |
| `IsEmbedded` | `Boolean` | Yes | No | — | True once EmbedWithin/EmbedWithinPanel has placed the container. |

### EmbedWithin

`Public Sub EmbedWithin(containingWindow As Window, left As Integer = 0, top As Integer = 0, width As Integer = -1, height As Integer = -1)`

API 1 `EmbedWithin(window, [left, top, width, height])`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `containingWindow` | `Window` | `ByVal` | Required |
| `left` | `Integer` | `ByVal` | `0` |
| `top` | `Integer` | `ByVal` | `0` |
| `width` | `Integer` | `ByVal` | `-1` |
| `height` | `Integer` | `ByVal` | `-1` |

Returns: no value.

### EmbedWithin (overload 2)

`Public Sub EmbedWithin(containingView As View, left As Integer = 0, top As Integer = 0, width As Integer = -1, height As Integer = -1)`

API 1 `EmbedWithin(container, [left, top, width, height])`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `containingView` | `View` | `ByVal` | Required |
| `left` | `Integer` | `ByVal` | `0` |
| `top` | `Integer` | `ByVal` | `0` |
| `width` | `Integer` | `ByVal` | `-1` |
| `height` | `Integer` | `ByVal` | `-1` |

Returns: no value.

### EmbedWithinPanel

`Public Sub EmbedWithinPanel(containingPanel As PagePanel, page As Integer, left As Integer = 0, top As Integer = 0, width As Integer = -1, height As Integer = -1)`

API 1 `EmbedWithinPanel(panel, page, [left, top, width, height])` for a PagePanel; pages must come from ClassicAddPage/ClassicRegisterPanelPage.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `containingPanel` | `PagePanel` | `ByVal` | Required |
| `page` | `Integer` | `ByVal` | Required |
| `left` | `Integer` | `ByVal` | `0` |
| `top` | `Integer` | `ByVal` | `0` |
| `width` | `Integer` | `ByVal` | `-1` |
| `height` | `Integer` | `ByVal` | `-1` |

Returns: no value.

### EmbedWithinPanel (overload 2)

`Public Sub EmbedWithinPanel(containingPanel As TabView, page As Integer, left As Integer = 0, top As Integer = 0, width As Integer = -1, height As Integer = -1)`

API 1 `EmbedWithinPanel` for a TabPanel (Buoy TabView).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `containingPanel` | `TabView` | `ByVal` | Required |
| `page` | `Integer` | `ByVal` | Required |
| `left` | `Integer` | `ByVal` | `0` |
| `top` | `Integer` | `ByVal` | `0` |
| `width` | `Integer` | `ByVal` | `-1` |
| `height` | `Integer` | `ByVal` | `-1` |

Returns: no value.
