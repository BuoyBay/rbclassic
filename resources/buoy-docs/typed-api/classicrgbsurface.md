---
title: "rbclassic \u00b7 ClassicRGBSurface"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicRGBSurface"]
dependencies: []
symbols: ["ClassicRGBSurface"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicRGBSurface

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicRGBSurface

`Public Class ClassicRGBSurface`

API 1 `RGBSurface` of a ClassicPicture. `Pixel(x, y)` reads and writes one pixel; coordinates outside the picture raise OutOfBoundsException. Translucent writes, `Transform` and `FloodFill` edit a cached copy that is written back once, on the next native use (see ClassicPicture), so loops of pixel writes cost O(1) each after the first. A translucent color on a picture without an alpha channel raises UnsupportedOperationException. Translucent pixels round-trip through premultiplied storage once written back, which legacy also documents as lossy.

### Pixel

`Public Function Pixel(x As Integer, y As Integer) As Color`

API 1 `RGBSurface.Pixel(x, y) As Color`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `x` | `Integer` | `ByVal` | Required |
| `y` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Color` |

### Pixel (overload 2)

`Public Sub Pixel(x As Integer, y As Integer, Assigns c As Color)`

API 1 `RGBSurface.Pixel(x, y) = c`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `x` | `Integer` | `ByVal` | Required |
| `y` | `Integer` | `ByVal` | Required |
| `c` | `Color` | `Assigns` | Required |

Returns: no value.

### Transform

`Public Sub Transform(map As Array Of Integer)`

API 1 `RGBSurface.Transform(map)`: each pixel's red, green and blue become `map(channel)`; alpha is unchanged. `map` must have exactly 256 entries in 0-255 (InvalidArgumentException otherwise).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `map` | `Array Of Integer` | `ByVal` | Required |

Returns: no value.

### Transform (overload 2)

`Public Sub Transform(redMap As Array Of Integer, greenMap As Array Of Integer, blueMap As Array Of Integer)`

API 1 `RGBSurface.Transform(redMap, greenMap, blueMap)`, one map per channel.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `redMap` | `Array Of Integer` | `ByVal` | Required |
| `greenMap` | `Array Of Integer` | `ByVal` | Required |
| `blueMap` | `Array Of Integer` | `ByVal` | Required |

Returns: no value.

### FloodFill

`Public Sub FloodFill(x As Integer, y As Integer, fillColor As Color)`

API 1 `RGBSurface.FloodFill(x, y, fillColor)`: the pixel at (x, y) and every pixel connected to it horizontally or vertically (4-connected; legacy says "adjacent" without defining diagonals) with exactly the same RGBA value become `fillColor`, with no blending or antialiasing.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `x` | `Integer` | `ByVal` | Required |
| `y` | `Integer` | `ByVal` | Required |
| `fillColor` | `Color` | `ByVal` | Required |

Returns: no value.
