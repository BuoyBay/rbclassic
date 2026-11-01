---
title: "rbclassic \u00b7 ClassicPicture"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicPicture"]
dependencies: []
symbols: ["ClassicPicture"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicPicture

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicPicture

`Public Class ClassicPicture`

API 1 `Picture` with the old constructors' meaning. `New ClassicPicture(w, h)` has an alpha channel and starts fully transparent; `New ClassicPicture(w, h, 24 &#124; 32)` is a legacy picture that starts opaque white and is returned to white by `ClearRect`. Depth 0 (vector Object2D pictures) raises UnsupportedOperationException, any other depth InvalidArgumentException, and sizes outside 1-32767 OutOfBoundsException — the exceptions legacy documents for this constructor.  Pixels live in a native `Picture`, exposed as `NativePicture`. Pixel operations Buoy cannot do in place (translucent `Pixel` writes, `ClearRect` on an alpha picture, `Transform`, `FloodFill`, `ApplyMask`) edit a cached straight-RGBA copy; the native picture is rebuilt once, on the next native draw or `NativePicture` read, as a new object with the same HiDPI scale. Read `NativePicture` again after pixel operations, and before each batch of direct native drawing, rather than keeping an old reference.  Legacy (non-alpha) pictures support API 1 masks (`Mask`, `ApplyMask`, `CopyMask`) and `Transparent = 1`. `NativePicture` holds the unmasked colors; `DrawPicture`, `ClassicCanvas.Backdrop` and `CompositedPicture` apply the mask.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `NativePicture` | `Picture` | Yes | No | — | The native picture holding the (unmasked) pixels. Reading it applies pending pixel edits (see the class note). |
| `CompositedPicture` | `Picture` | Yes | No | — | A snapshot of the picture as it is drawn: for a legacy picture with a mask or `Transparent = 1`, a new alpha Picture with the mask applied (white mask hides, black shows; gray is partial); otherwise the current native picture. |
| `Width` | `Integer` | Yes | No | — | API 1 `Picture.Width` in pixels. |
| `Height` | `Integer` | Yes | No | — | API 1 `Picture.Height` in pixels. |
| `Depth` | `Integer` | Yes | No | — | API 1 `Picture.Depth` — always 32 for a pixel picture. |
| `HasAlphaChannel` | `Boolean` | Yes | No | — | API 1 `Picture.HasAlphaChannel` — False for depth-constructed pictures. |
| `Graphics` | `ClassicGraphics` | Yes | No | — | API 1 `Picture.Graphics` — the same ClassicGraphics every time, so its ForeColor/TextFont/pen state persists across reads. |
| `RGBSurface` | `ClassicRGBSurface` | Yes | No | — | API 1 `Picture.RGBSurface` — direct pixel access (see ClassicRGBSurface). |
| `Transparent` | `Integer` | No | No | — | API 1 `Picture.Transparent`: 0 (opaque) or 1 (white pixels are drawn transparent). Only legacy pictures can use 1; an alpha picture raises UnsupportedOperationException, other values InvalidArgumentException. |

### Constructor

`Public Sub Constructor(width As Integer, height As Integer)`

API 1 `New Picture(width, height)`: alpha channel, initially transparent.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `width` | `Integer` | `ByVal` | Required |
| `height` | `Integer` | `ByVal` | Required |

Returns: no value.

### Constructor (overload 2)

`Public Sub Constructor(width As Integer, height As Integer, depth As Integer)`

API 1 `New Picture(width, height, depth)`: depth 24 or 32 makes a legacy, initially opaque white picture (24 is accepted for source compatibility and is 32-bit, as in legacy).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `width` | `Integer` | `ByVal` | Required |
| `height` | `Integer` | `ByVal` | Required |
| `depth` | `Integer` | `ByVal` | Required |

Returns: no value.

### Constructor (overload 3)

`Public Sub Constructor(native As Picture)`

Wraps an existing Buoy `Picture` (loaded, decoded or drawn) as an alpha-channel picture. Raises NilObjectException for Nil.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `native` | `Picture` | `ByVal` | Required |

Returns: no value.

### Mask

`Public Function Mask(createIfMissing As Boolean = True) As ClassicPicture`

API 1 `Picture.Mask([createIfMissing = True])`: the live mask of a legacy picture (white hides, black shows). A new mask starts black, so creating it does not change the picture's appearance (legacy does not document the initial contents). Returns Nil for alpha pictures, as legacy documents, and when no mask exists and createIfMissing is False.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `createIfMissing` | `Boolean` | `ByVal` | `True` |

#### Returns

| Type |
| --- |
| `ClassicPicture` |

### ApplyMask

`Public Sub ApplyMask(theMask As ClassicPicture)`

API 1 `Picture.ApplyMask(mask)`: on an alpha picture the alpha channel becomes 255 minus the mask's gray level (the mean of its R, G and B); on a legacy picture the mask is replaced by a copy of `mask`. The mask must have the picture's size (InvalidArgumentException otherwise; legacy leaves other sizes undefined). Fully transparent pixels of an alpha picture carry no color in premultiplied storage, so revealing them shows black.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `theMask` | `ClassicPicture` | `ByVal` | Required |

Returns: no value.

### CopyMask

`Public Function CopyMask() As ClassicPicture`

API 1 `Picture.CopyMask`: for an alpha picture a new legacy picture whose gray level is 255 minus each pixel's alpha; for a legacy picture a copy of its mask, or Nil when it has none. The copy is not updated by later drawing.

No parameters.

#### Returns

| Type |
| --- |
| `ClassicPicture` |
