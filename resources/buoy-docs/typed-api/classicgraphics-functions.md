---
title: "rbclassic \u00b7 ClassicGraphics functions"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: []
dependencies: []
symbols: ["ClassicCMY", "ClassicHSV", "ClassicRGB"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicGraphics functions

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicGraphics functions

### ClassicRGB

`Public Function ClassicRGB(red As Integer, green As Integer, blue As Integer, alpha As Integer = 0) As Color`

API 1 `RGB(red, green, blue, [alpha = 0])`: channels 0-255; `alpha` 0 is opaque, 255 fully transparent. Raises InvalidArgumentException outside 0-255.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `red` | `Integer` | `ByVal` | Required |
| `green` | `Integer` | `ByVal` | Required |
| `blue` | `Integer` | `ByVal` | Required |
| `alpha` | `Integer` | `ByVal` | `0` |

#### Returns

| Type |
| --- |
| `Color` |

### ClassicHSV

`Public Function ClassicHSV(hue As Double, saturation As Double, value As Double, alpha As Integer = 0) As Color`

API 1 `HSV(hue, saturation, value, [alpha = 0])`: hue, saturation and value are 0-1 (hue 1.0 is red again, as in legacy's `HSV(1.0, 1.0, 1.0)` example); `alpha` 0 is opaque, 255 fully transparent.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `hue` | `Double` | `ByVal` | Required |
| `saturation` | `Double` | `ByVal` | Required |
| `value` | `Double` | `ByVal` | Required |
| `alpha` | `Integer` | `ByVal` | `0` |

#### Returns

| Type |
| --- |
| `Color` |

### ClassicCMY

`Public Function ClassicCMY(cyan As Double, magenta As Double, yellow As Double, alpha As Integer = 0) As Color`

API 1 `CMY(cyan, magenta, yellow, [alpha = 0])`: naive CMY, channels 0-1; `alpha` 0 is opaque, 255 fully transparent.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `cyan` | `Double` | `ByVal` | Required |
| `magenta` | `Double` | `ByVal` | Required |
| `yellow` | `Double` | `ByVal` | Required |
| `alpha` | `Integer` | `ByVal` | `0` |

#### Returns

| Type |
| --- |
| `Color` |
