---
title: "rbclassic \u00b7 ClassicGraphics"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicGraphics"]
dependencies: []
symbols: ["ClassicGraphics"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicGraphics

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicGraphics

`Public Class ClassicGraphics`

API 1 `Graphics` over a native Buoy `Graphics`, with legacy's ambient drawing state. Obtain one from `ClassicPicture.Graphics`, from `ClassicCanvas`'s `Paint(g, areas)` event, from `Clip`, or wrap a native paint-cycle context with `New ClassicGraphics(g)` (valid only as long as that context is).  Limitations (each raises instead of approximating): `ClearRect`/`Pixel` on a context not backed by a ClassicPicture or on a fractional `Clip`; `TextAscent`, `TextHeight`, `StringHeight` and wrapped `DrawString` where the font metrics cannot be verified (every non-Linux target); and `DrawPolygon` with PenWidth different from PenHeight. See notes/graphics.md for the geometry rules.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `TextFont` | `String` | No | No | `"System"` | API 1 `TextFont` (default "System"). |
| `TextSize` | `Double` | No | No | `12.0` | API 1 `TextSize` in points (default 12). 0 reads back as 0 and draws at the system size, taken as 12 (the shim's probed legacy default). |
| `PenWidth` | `Double` | No | No | `1.0` | API 1 `PenWidth` (default 1): the horizontal extent of the pen. |
| `PenHeight` | `Double` | No | No | `1.0` | API 1 `PenHeight` (default 1): the vertical extent of the pen. |
| `Bold` | `Boolean` | No | No | `False` | API 1 `Bold` text style. |
| `Italic` | `Boolean` | No | No | `False` | API 1 `Italic` text style. |
| `Underline` | `Boolean` | No | No | `False` | API 1 `Underline` text style. |
| `NativeGraphics` | `Graphics` | Yes | No | — | The root native context drawn into (without this object's Clip origin or clip). For a picture this applies pending pixel edits and follows `ClassicPicture.NativePicture`; read it again after pixel operations. |
| `ForeColor` | `Color` | No | No | — | API 1 `ForeColor` (default black). Nil raises NilObjectException. |
| `Transparency` | `Double` | No | No | — | API 1 `Transparency`: 0.0 (opaque) to 100.0 (fully transparent), composited with color and picture alpha. Other values raise InvalidArgumentException. |
| `Width` | `Integer` | Yes | No | — | API 1 `Width` of the drawable area in pixels (a Clip's requested width). |
| `Height` | `Integer` | Yes | No | — | API 1 `Height` of the drawable area in pixels (a Clip's requested height). |
| `TextAscent` | `Double` | Yes | No | — | API 1 `TextAscent`: the font's ascent above the baseline, from the face the native Graphics draws with. Raises UnsupportedOperationException when that face's metrics cannot be verified (all non-Linux targets). |
| `TextHeight` | `Double` | Yes | No | — | API 1 `TextHeight`: the font's line height (Cairo's ascent + descent + line gap). Same availability as TextAscent. |

### Constructor

`Public Sub Constructor(g As Graphics)`

Wraps a native drawing context, e.g. a Buoy `Canvas.Paint` parameter.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `g` | `Graphics` | `ByVal` | Required |

Returns: no value.

### Clip

`Public Function Clip(x As Double, y As Double, width As Double, height As Double) As ClassicGraphics`

API 1 `Clip(x, y, width, height) As Graphics`: a child context whose origin is (x, y) in this context and whose drawing is confined to the rectangle (intersected with this context's own clip). Its Width and Height are the requested size even beyond the parent's edges, as legacy documents. The child starts with a copy of this context's ForeColor, text, pen and Transparency settings. Negative sizes raise InvalidArgumentException.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `width` | `Double` | `ByVal` | Required |
| `height` | `Double` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `ClassicGraphics` |

### Clip (overload 2)

`Public Function Clip(r As Rect) As ClassicGraphics`

API 1 `Clip(r As Rect) As Graphics`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `r` | `Rect` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `ClassicGraphics` |

### DrawLine

`Public Sub DrawLine(x1 As Double, y1 As Double, x2 As Double, y2 As Double)`

API 1 `DrawLine(x1, y1, x2, y2)` with ForeColor and the pen. With PenWidth = PenHeight this is the shim's probed legacy line; otherwise the line is the convex hull of a PenWidth x PenHeight rectangle centered on each end pixel.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `x1` | `Double` | `ByVal` | Required |
| `y1` | `Double` | `ByVal` | Required |
| `x2` | `Double` | `ByVal` | Required |
| `y2` | `Double` | `ByVal` | Required |

Returns: no value.

### DrawRect

`Public Sub DrawRect(x As Double, y As Double, width As Double, height As Double)`

API 1 `DrawRect(x, y, width, height)` outline: sides PenWidth wide and top/bottom PenHeight tall, centered on the shim's pixel-center edges.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `width` | `Double` | `ByVal` | Required |
| `height` | `Double` | `ByVal` | Required |

Returns: no value.

### FillRect

`Public Sub FillRect(x As Double, y As Double, width As Double, height As Double)`

API 1 `FillRect(x, y, width, height)`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `width` | `Double` | `ByVal` | Required |
| `height` | `Double` | `ByVal` | Required |

Returns: no value.

### DrawOval

`Public Sub DrawOval(x As Double, y As Double, width As Double, height As Double)`

API 1 `DrawOval(x, y, width, height)` outline. The outer edge stays on the oval's bounds (the shim's probed rule); the ring is PenWidth thick at the sides and PenHeight at the top and bottom.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `width` | `Double` | `ByVal` | Required |
| `height` | `Double` | `ByVal` | Required |

Returns: no value.

### FillOval

`Public Sub FillOval(x As Double, y As Double, width As Double, height As Double)`

API 1 `FillOval(x, y, width, height)`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `width` | `Double` | `ByVal` | Required |
| `height` | `Double` | `ByVal` | Required |

Returns: no value.

### DrawRoundRect

`Public Sub DrawRoundRect(x As Double, y As Double, width As Double, height As Double, arcWidth As Double, arcHeight As Double)`

API 1 `DrawRoundRect(x, y, width, height, arcWidth, arcHeight)`. The arcs are the distances from each corner at which the corner curve begins (legacy's definition); unequal arcs give elliptical corners.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `width` | `Double` | `ByVal` | Required |
| `height` | `Double` | `ByVal` | Required |
| `arcWidth` | `Double` | `ByVal` | Required |
| `arcHeight` | `Double` | `ByVal` | Required |

Returns: no value.

### FillRoundRect

`Public Sub FillRoundRect(x As Double, y As Double, width As Double, height As Double, arcWidth As Double, arcHeight As Double)`

API 1 `FillRoundRect(x, y, width, height, arcWidth, arcHeight)`; unequal arcs give elliptical corners over the same w+1 x h+1 area.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `width` | `Double` | `ByVal` | Required |
| `height` | `Double` | `ByVal` | Required |
| `arcWidth` | `Double` | `ByVal` | Required |
| `arcHeight` | `Double` | `ByVal` | Required |

Returns: no value.

### FillPolygon

`Public Sub FillPolygon(points As Array Of Double)`

API 1 `FillPolygon(points)`: a 1-based array (element 0 ignored) of x, y pairs; vertices are pixel-corner coordinates, so an axis-aligned polygon covers exactly the pixels inside it.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `points` | `Array Of Double` | `ByVal` | Required |

Returns: no value.

### FillPolygon (overload 2)

`Public Sub FillPolygon(points As Array Of Integer)`

`FillPolygon` for an Integer array (the original API 1 signature).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `points` | `Array Of Integer` | `ByVal` | Required |

Returns: no value.

### DrawPolygon

`Public Sub DrawPolygon(points As Array Of Double)`

API 1 `DrawPolygon(points)`: the closed outline through the points, stroked with the pen centered on pixel centers (like DrawLine). PenWidth must equal PenHeight (UnsupportedOperationException).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `points` | `Array Of Double` | `ByVal` | Required |

Returns: no value.

### DrawPolygon (overload 2)

`Public Sub DrawPolygon(points As Array Of Integer)`

`DrawPolygon` for an Integer array (the original API 1 signature).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `points` | `Array Of Integer` | `ByVal` | Required |

Returns: no value.

### StringHeight

`Public Function StringHeight(text As String, wrapWidth As Double) As Double`

API 1 `StringHeight(text, wrapWidth)`: TextHeight times the number of lines `DrawString(text, x, y, wrapWidth)` draws (one line when wrapWidth <= 0). As legacy documents, this is the font's height, not the ink height of the text. Same availability as TextAscent.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `text` | `String` | `ByVal` | Required |
| `wrapWidth` | `Double` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### DrawString

`Public Sub DrawString(text As String, x As Double, y As Double, wrapWidth As Double = 0.0, condense As Boolean = False)`

API 1 `DrawString(text, x, y, [wrapWidth = 0], [condense = False])`, baseline at `y`, in ForeColor, TextFont, TextSize and the text styles.  - wrapWidth <= 0: one line (line breaks are passed to the native renderer unchanged). - wrapWidth > 0, condense False: greedy word wrap at spaces using StringWidth; CR, LF and CRLF start new lines; a word wider than wrapWidth is broken between characters (combining sequences kept together). Line n has its baseline at y + n * TextHeight, so this needs verified font metrics (UnsupportedOperationException on non-Linux targets). - wrapWidth > 0, condense True: one line (line breaks as spaces); if it is wider than wrapWidth it is cut at a character boundary and "..." appended so the result fits; if "..." alone does not fit, nothing is drawn.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `text` | `String` | `ByVal` | Required |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `wrapWidth` | `Double` | `ByVal` | `0.0` |
| `condense` | `Boolean` | `ByVal` | `False` |

Returns: no value.

### StringWidth

`Public Function StringWidth(text As String) As Double`

API 1 `StringWidth(text)` in the current text settings. As in legacy, line breaks are measured as spaces (multiple lines are not handled). Where the font is verified (Linux) this is the text's advance width, which counts spaces and side bearings like legacy's; otherwise it is the runtime's MeasureStringWidth (ink width on Linux).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `text` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### DrawPicture

`Public Sub DrawPicture(image As Picture, x As Double, y As Double)`

API 1 `DrawPicture(image, x, y)` at natural size.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `image` | `Picture` | `ByVal` | Required |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |

Returns: no value.

### DrawPicture (overload 2)

`Public Sub DrawPicture(image As Picture, x As Double, y As Double, destWidth As Double, destHeight As Double)`

API 1 `DrawPicture(image, x, y, destWidth, destHeight)`: crops (not scales) to the top-left destWidth x destHeight of `image`.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `image` | `Picture` | `ByVal` | Required |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `destWidth` | `Double` | `ByVal` | Required |
| `destHeight` | `Double` | `ByVal` | Required |

Returns: no value.

### DrawPicture (overload 3)

`Public Sub DrawPicture(image As Picture, x As Double, y As Double, destWidth As Double, destHeight As Double, sourceX As Double, sourceY As Double, sourceWidth As Double, sourceHeight As Double)`

API 1 `DrawPicture(image, x, y, destWidth, destHeight, sourceX, sourceY, sourceWidth, sourceHeight)`: the source rectangle scaled into the destination rectangle. Negative sizes raise InvalidArgumentException (legacy leaves them undefined).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `image` | `Picture` | `ByVal` | Required |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `destWidth` | `Double` | `ByVal` | Required |
| `destHeight` | `Double` | `ByVal` | Required |
| `sourceX` | `Double` | `ByVal` | Required |
| `sourceY` | `Double` | `ByVal` | Required |
| `sourceWidth` | `Double` | `ByVal` | Required |
| `sourceHeight` | `Double` | `ByVal` | Required |

Returns: no value.

### DrawPicture (overload 4)

`Public Sub DrawPicture(image As ClassicPicture, x As Double, y As Double)`

`DrawPicture(image, x, y)` for a ClassicPicture (mask applied).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `image` | `ClassicPicture` | `ByVal` | Required |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |

Returns: no value.

### DrawPicture (overload 5)

`Public Sub DrawPicture(image As ClassicPicture, x As Double, y As Double, destWidth As Double, destHeight As Double)`

`DrawPicture(image, x, y, destWidth, destHeight)` (crop) for a ClassicPicture.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `image` | `ClassicPicture` | `ByVal` | Required |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `destWidth` | `Double` | `ByVal` | Required |
| `destHeight` | `Double` | `ByVal` | Required |

Returns: no value.

### DrawPicture (overload 6)

`Public Sub DrawPicture(image As ClassicPicture, x As Double, y As Double, destWidth As Double, destHeight As Double, sourceX As Double, sourceY As Double, sourceWidth As Double, sourceHeight As Double)`

Source-rectangle `DrawPicture` for a ClassicPicture.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `image` | `ClassicPicture` | `ByVal` | Required |
| `x` | `Double` | `ByVal` | Required |
| `y` | `Double` | `ByVal` | Required |
| `destWidth` | `Double` | `ByVal` | Required |
| `destHeight` | `Double` | `ByVal` | Required |
| `sourceX` | `Double` | `ByVal` | Required |
| `sourceY` | `Double` | `ByVal` | Required |
| `sourceWidth` | `Double` | `ByVal` | Required |
| `sourceHeight` | `Double` | `ByVal` | Required |

Returns: no value.

### ClearRect

`Public Sub ClearRect(x As Integer, y As Integer, width As Integer, height As Integer)`

API 1 `ClearRect(x, y, width, height)` on a ClassicPicture's Graphics (or a whole-pixel Clip of it): the integer rectangle, limited to the clip, returns to transparent (alpha picture) or opaque white (depth picture). On other contexts raises UnsupportedOperationException (Buoy cannot erase a paint context).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `x` | `Integer` | `ByVal` | Required |
| `y` | `Integer` | `ByVal` | Required |
| `width` | `Integer` | `ByVal` | Required |
| `height` | `Integer` | `ByVal` | Required |

Returns: no value.

### Pixel

`Public Function Pixel(x As Integer, y As Integer) As Color`

API 1 `Graphics.Pixel(x, y) As Color` — picture-backed contexts only (see ClassicRGBSurface); local to a Clip.

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

API 1 `Graphics.Pixel(x, y) = c` — picture-backed contexts only.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `x` | `Integer` | `ByVal` | Required |
| `y` | `Integer` | `ByVal` | Required |
| `c` | `Color` | `Assigns` | Required |

Returns: no value.
