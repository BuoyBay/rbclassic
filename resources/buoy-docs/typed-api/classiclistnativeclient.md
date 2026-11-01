---
title: "rbclassic \u00b7 ClassicListNativeClient"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicListNativeClient"]
dependencies: []
symbols: ["ClassicListNativeClient"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicListNativeClient

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicListNativeClient

`Public Interface ClassicListNativeClient`

Receives native list events. ClassicListBox implements it; the bridge holds its client weakly.

### ClassicListNativeActivated

`Sub ClassicListNativeActivated(row As Integer)`

A row was activated by the mouse (GTK double-click). Keyboard activation (Return/Enter) is filtered out and arrives as a key.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `row` | `Integer` | `ByVal` | Required |

Returns: no value.

### ClassicListNativeKey

`Function ClassicListNativeKey(keyval As Integer, codepoint As Integer, modifiers As Integer) As Boolean`

A key was pressed while the list has focus. Return True to consume it before the native list handles it.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `keyval` | `Integer` | `ByVal` | Required |
| `codepoint` | `Integer` | `ByVal` | Required |
| `modifiers` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### ClassicListNativeHeader

`Sub ClassicListNativeHeader(column As Integer)`

The user clicked the header of `column`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `column` | `Integer` | `ByVal` | Required |

Returns: no value.

### ClassicListNativeSelection

`Sub ClassicListNativeSelection()`

The native multiple-selection set changed.

No parameters.

Returns: no value.

### ClassicListNativeResized

`Sub ClassicListNativeResized(width As Integer)`

The visible width of the list changed.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `width` | `Integer` | `ByVal` | Required |

Returns: no value.
