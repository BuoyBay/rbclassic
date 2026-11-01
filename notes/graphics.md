# ClassicGraphics implementation notes

Owned files: `modules/ClassicGraphics.bui`, `tests/classic_graphics_test.bui` and `tests/classic_mouse_verify.py` (repo root), and this note. The module uses a plain `Import RBFoundation` (the bundled shim) and no sibling Classic modules. It never imports `rbclassic`.

## Integration requirements (parent)

- Exports are unchanged: `Public Import ClassicGraphics` exports the classes `ClassicPicture`, `ClassicRGBSurface`, `ClassicGraphics` and `ClassicCanvas`. The global color functions still need the selective line:

  ```
  Public Import ClassicGraphics.{ ClassicRGB, ClassicHSV, ClassicCMY }
  ```

- Every new member is a method or property of those classes, so no new selective import is needed.
- All other top-level helpers are `Internal`. The two Cairo FFI structures (`ClassicCairoFontExtents`, `ClassicCairoTextExtents`) exist only on Linux; they are structures, which cannot take an access modifier.
- **No new package or native staging.** The Linux font metrics use `Optional Declare` into the system `libcairo.so.2`, the library the Linux GUI runtime itself links. Nothing is bundled, and there is no new helper under `native/graphics`. The library is checked with `System.IsLibraryAvailable` before use. On macOS and Windows no declares are compiled (`#If TargetLinux`).
- With serialio, the repository's `packages/processkit-0.1.0.buipkg` and the usual Xojo dependency packages staged in a temp `packages/`, the current entry `RBClassic.bui` checks with 0 errors (default target).

## Source rewrites

Buoy already has `Picture`, `Graphics`, `Canvas`, and `Color.RGB`, with different meanings, so ported code must change these names. The worst trap is `New Picture(w, h, 32)`: it compiles and creates a picture with scale 32.

| API 1 | Rewrite |
|---|---|
| `New Picture(w, h, depth)` / `New Picture(w, h)` | `New ClassicPicture(w, h, depth)` / `New ClassicPicture(w, h)` |
| a loaded/decoded `Picture` | `New ClassicPicture(pic)` |
| `g As Graphics` | `g As ClassicGraphics` |
| `Inherits Canvas`; `Paint(g, areas() As REALbasic.Rect)` | `Inherits ClassicCanvas`; `Handle Paint(g As ClassicGraphics, areas As Array Of Rect)` |
| `RGB`/`HSV`/`CMY(..., alpha)` | `ClassicRGB`/`ClassicHSV`/`ClassicCMY` |
| `Canvas.Refresh`/`RefreshRect` | `Invalidate`/`Invalidate(x, y, w, h)` (deferred) |
| `Dim pts(6) As Integer` for polygons | `Dim pts As Array Of Integer = [0, x1, y1, ...]` (element 0 still ignored) |

## Supported behavior

Semantics follow the archived docs.xojo.com pages (2014–2020) and the current deprecated-member pages at documentation.xojo.com (`Graphics.DrawString`, `StringHeight`, `TextAscent`, `FillPolygon`, `FillRoundRect`, `Clip`, `RGBSurface`, `Picture.Mask`/`ApplyMask`/`CopyMask`/`Transparent`). Where Xojo leaves something undefined, the choice made here is stated.

- **Colors.**
  - `ClassicRGB(r, g, b, alpha = 0)` takes channels from 0 to 255. Alpha 0 is opaque and 255 is fully transparent; this is the reverse of Buoy's `Color.A`.
  - `ClassicHSV` takes hue, saturation, and value from 0 to 1, and hue 1.0 is red.
  - `ClassicCMY` uses the naive formula `1 - channel`.
  - The shim's `c.Alpha` extension round-trips the alpha value.
  - Out-of-range input raises `InvalidArgumentException`.
- **ClassicPicture.**
  - `(w, h)` creates a picture with an alpha channel that starts transparent.
  - `(w, h, 24|32)` creates a legacy picture that starts opaque white. `HasAlphaChannel` is False and `Depth` is 32.
  - Depth 0 raises `UnsupportedOperationException`. Any other bad depth raises `InvalidArgumentException`. A size outside 1–32767 raises `OutOfBoundsException`.
  - `Graphics` and `RGBSurface` return the same instance on every read.
- **Pixel cache (efficient pixel mutation).**
  - Translucent `Pixel` writes, `ClearRect` on alpha pictures, `Transform`, `FloodFill` and `ApplyMask` edit a cached straight-RGBA copy. After the first operation, which copies the backing store once, each further operation costs O(1) per pixel.
  - The native picture is rebuilt once, when it is next used natively: a `ClassicGraphics` draw, a `NativePicture` or `NativeGraphics` read, or drawing the picture elsewhere. The rebuild keeps the HiDPI scale and gives `NativePicture` a new object.
  - Native drawing drops the cache, so the next read sees the drawing.
  - Opaque writes with no cache open are still in-place 1×1 fills.
  - Cached reads return the stored straight value. A fully transparent pixel reads as 0,0,0,0, as premultiplied storage would.
  - Measured: 16 384 translucent writes on a 128×128 picture took 9 ms. In the previous wave each such write rebuilt the whole picture.
- **ClassicGraphics state.**
  - `ForeColor` defaults to black; assigning Nil raises `NilObjectException`.
  - `TextFont` defaults to "System". `TextSize` defaults to 12; a value of 0 draws and measures at 12.
  - `PenWidth` and `PenHeight` default to 1. `Bold`, `Italic` and `Underline` are supported.
  - `Transparency` ranges from 0 to 100.
  - Native Bold/Italic/Underline state is restored after every text call.
- **Clip.**
  - `Clip(x, y, w, h)` and `Clip(r As Rect)` return a child `ClassicGraphics`.
  - Coordinates are local to the child. Drawing is clipped to the child's rectangle intersected with the parent's clip, so nested clips cannot escape their parent.
  - `Width`/`Height` are the requested size, even beyond the parent's edges, as Xojo documents.
  - The child starts with a copy of the parent's color, text, pen and Transparency settings; later changes do not propagate either way. Xojo does not document the child's initial state.
  - Every operation brackets the native context with `Save`/`ClipToRect`/`Translate`/`Restore`, so the parent's native state is not disturbed.
  - `Pixel` and `ClearRect` on a clip are local and limited to the clip. `Pixel` outside the clip raises `OutOfBoundsException`.
  - Pixel operations need whole-pixel clip bounds; otherwise they raise `UnsupportedOperationException`.
- **Shapes.** `DrawLine`, `DrawRect`/`FillRect`, `DrawOval`/`FillOval` and `DrawRoundRect`/`FillRoundRect` with equal pens and equal arcs keep the shim's probed Xojo geometry: fills cover w+1 by h+1 pixels, strokes sit on pixel centers, and an oval keeps its outer edge. The following cases are filled paths built on that same geometry:
  - **Asymmetric pens (PenWidth ≠ PenHeight).** These model a rectangular pen of PenWidth × PenHeight.
    - `DrawLine` fills the convex hull of the pen rectangle centered on each end pixel. A horizontal line is PenHeight tall and a vertical line PenWidth wide, both including the end pixels.
    - `DrawRect` and `DrawRoundRect` fill one ring centered on the shim's stroke centerline. The sides are PenWidth wide and the top and bottom are PenHeight tall.
    - `DrawOval` keeps the outer bounds of w+1 × h+1 and insets the inner ellipse by PenWidth and PenHeight.
    - Each ring is one path, so with `Transparency` the corners composite once.
  - **Elliptical corners (arcWidth ≠ arcHeight).** Xojo defines the arcs as the distance from the corner at which the curve begins, so they are the horizontal and vertical radii. They are clamped to half the size, and quarter-ellipse corners use the standard cubic approximation. `FillRoundRect` covers w+1 × h+1; `DrawRoundRect` uses the ring above.
  - **Polygons.** `FillPolygon` and `DrawPolygon` take an `Array Of Integer` (the original API 1 signature) or an `Array Of Double`.
    - Arrays are 1-based: element 0 is ignored, then x, y pairs. An array with fewer than one pair or an odd pair count raises `InvalidArgumentException`.
    - `FillPolygon` vertices are pixel-corner coordinates, so an axis-aligned square [4..8) covers pixels 4–7 exactly.
    - `DrawPolygon` closes the outline and strokes it centered on pixel centers with `PenWidth` and the native join.
- **Text.**
  - `DrawString(text, x, y)` draws one line on baseline `y`.
  - **Metrics (Linux).** `TextAscent`, `TextHeight` and `StringHeight(text, wrapWidth)` come from `cairo_font_extents` in a private Cairo image context. That context selects the same toy font as the runtime (family, size, weight, slant). It never touches the runtime's `NativeHandle`, which is a wrapper (BUI-001).
    - Before a face is used, the ink extents of a probe string in that context must equal the runtime's own `MeasureStringWidth`/`MeasureStringHeight` (tolerance 0.01). On a mismatch the members raise `UnsupportedOperationException` instead of returning another font's numbers.
    - Results are cached per (family, size, Bold, Italic), up to 256 entries.
    - `TextHeight` is Cairo's line height (ascent + descent + line gap). `StringHeight` is `TextHeight` × the number of lines drawn; as Xojo documents, it is the font's height, not the ink height ("a" and "A" are equal).
  - **StringWidth.** Line breaks count as spaces. On Linux, when the face is verified, the result is the text's advance width, so spaces count as in Xojo. Elsewhere, or when the face is not verified, it is the runtime's `MeasureStringWidth`; on Linux that is the ink width (BUI-002).
  - **Wrapping (wrapWidth > 0, condense False).** Wrapping is greedy at spaces, using `StringWidth`.
    - CR, LF and CRLF start new lines.
    - A word wider than `wrapWidth` breaks between characters.
    - Line *n* has its baseline at `y + n × TextHeight`.
    - This needs verified metrics, so it is Linux-only.
  - **Condense (wrapWidth > 0, condense True).** The text is drawn on one line, with line breaks as spaces. If it is too wide, it is cut at a character boundary and "..." (three periods, as Xojo documents) is appended so the result fits. If "..." alone does not fit, nothing is drawn. Condense works on all targets because it uses `StringWidth`.
  - **Character boundaries.** Combining marks (U+0300–036F, 1AB0–1AFF, 1DC0–1DFF, 20D0–20FF, FE20–FE2F), variation selectors, emoji modifiers and ZWJ sequences stay with their base character. This is not full UAX #29: Hangul jamo and Indic clusters are not joined, and the Linux toy renderer does not shape them anyway (BUI-002).
- **DrawPicture.**
  - The 3-argument form draws at natural size.
  - The 5-argument form crops, as Xojo documents.
  - The 9-argument form scales a source rectangle into the destination rectangle.
  - `Transparency` fades the drawn picture.
  - Drawing a `ClassicPicture` applies its legacy mask or `Transparent` setting.
- **RGBSurface.**
  - `Pixel` reads and writes single pixels; out-of-range coordinates raise `OutOfBoundsException`.
  - `Transform(map)` and `Transform(redMap, greenMap, blueMap)` map R, G and B and leave alpha unchanged. Each map must have exactly 256 entries in 0–255; otherwise they raise `InvalidArgumentException`.
  - `FloodFill(x, y, c)` uses a scanline fill over 4-connected pixels whose RGBA exactly equals the seed's. Xojo says "adjacent" without defining diagonals. The fill does not blend or antialias.
- **Masks (legacy pictures).**
  - `Mask([createIfMissing = True])` returns the live mask: white hides, black shows, gray is partial.
    - A new mask starts black, so creating one does not change the picture. Xojo does not document the initial contents.
    - It returns Nil for alpha pictures, as documented, and when no mask exists and `createIfMissing` is False.
  - `ApplyMask(m)` on an alpha picture sets alpha to 255 minus the mask's gray level (the rounded mean of R, G and B). On a legacy picture it replaces the mask with a copy.
  - `CopyMask` on an alpha picture returns the equivalent gray legacy mask. On a legacy picture it returns a copy of the mask, or Nil when there is none.
  - A mask of a different size raises `InvalidArgumentException`.
  - `Transparent` takes 0 or 1 (1 means white is transparent). Any other value raises `InvalidArgumentException`; setting 1 on an alpha picture raises `UnsupportedOperationException`.
  - `NativePicture` keeps the unmasked colors. `CompositedPicture`, `DrawPicture` and `ClassicCanvas.Backdrop` apply the mask.
- **ClearRect.** Pixels return to transparent (alpha picture) or white (legacy picture), as documented for 2011r4+.
- **ClassicCanvas.**
  - `Backdrop` (with mask) is drawn before `Paint`.
  - `Paint(g, areas)` always passes an empty `areas`, which Xojo defines as a full redraw.
  - `MouseDown` gates `MouseDrag`/`MouseUp`. `MouseMove`, `MouseEnter` and `MouseExit` are also bridged.
  - Coordinates are local and floored.
  - `Invalidate` overloads are deferred.

## Explicit limitations (raise or are absent instead of approximating)

- `TextAscent`, `TextHeight`, `StringHeight` and wrapped `DrawString` raise `UnsupportedOperationException` on macOS and Windows. Buoy 0.72.0 exposes no font-metric API there; Core Text and GDI+ are not reachable from the Graphics wrapper. They also raise on Linux when libcairo is missing or the face check fails.
- `DrawPolygon` with PenWidth ≠ PenHeight raises `UnsupportedOperationException`: a union of per-edge pen hulls would double-blend translucent ink at the joins.
- The fill rule for self-intersecting polygons is the native renderer's and was not tested; only simple polygons were tested.
- Asymmetric-pen, elliptical-corner and polygon pixel geometry is defined above. It was **not** probed against real Xojo; the shim's probe covered only symmetric shapes.
- `ClearRect`/`Pixel` raise on paint-cycle contexts and fractional clips. Translucent pixels on legacy pictures raise.
- `DrawPicture` with negative sizes raises.
- Partial-alpha pixels shift by about one unit through premultiplied storage once written back. Scaled drawing blends at the picture edge.
- The cache is invalidated by `NativePicture`/`NativeGraphics` reads. Code that keeps an old native reference and draws through it later bypasses that invalidation: read the reference again before each batch.
- **Not provided:**
  - `TextUnit`
  - `DrawObject` and Object2D
  - Canvas `Refresh`/`RefreshRect`. These are synchronous in Xojo, and Buoy 0.72.0 has only deferred `Invalidate`/`InvalidateRect` plus offscreen `RenderTo`; nothing forces an on-screen paint before returning.
  - Dirty `areas` rectangles
  - `DoubleClick`, `KeyDown` and `KeyUp`
  - `Canvas.Graphics`

## Verification (2026-10-31, Buoy 0.72.0)

- **Compiler checks.** `buoy <file> --check --diagnostic-format json --target T` passed for `ClassicGraphics.bui` and `classic_graphics_test.bui` on x86_64/arm64 × linux/darwin/windows. Every run exited 0 with 0 errors. The only warning is the upstream `XojoDesktop.bui:160` extension `Show` warning. These checks are compile-only for darwin, windows and arm64-linux.
- **Build environment.** The test was built on the Linux x86_64 host in a temp directory, with `packages/` copies of Xojo, sqlite3, postgres, xml, regex, crypto, zip and Variant from `/usr/share/buoy/packages`.
  - Wrapper `/usr/local/bin/buoy` sha256 `7c9714fb…acd3`.
  - Runtime `buoy_ui.so` sha256 `44ccfebe…7c50`, the known 0.72.0 runtime.
- **Behavior run.** The binary ran in `buoy:0.72.0-gui` with `docker run --rm --network none`, a unique name, `--entrypoint /bin/bash`, `timeout 120 dbus-run-session -- xvfb-run -a ./classic_graphics_test`. Output: `16384 translucent pixel writes: 9 ms` / `classic_graphics: ok`.
- **Container fixture.** libcairo2 1.18.0-3build1. `fc-match System` resolves to DejaVu Sans Book.
- **Assertion coverage.** The assertions are independent of the implementation:
  - fixed pixel values;
  - ink rows checked against ascent and line height;
  - wrapped and condensed output pixel-identical to hand-drawn lines;
  - decomposed "é" kept together when wrapping;
  - clip containment and nesting;
  - polygon and pen bounds;
  - single compositing of a translucent asymmetric rect;
  - elliptical versus circular corner pixels;
  - Transform and flood connectivity;
  - mask, CopyMask and ApplyMask values;
  - masked Backdrop through `RenderTo`;
  - every new exception path.
- **Mouse regression.** `xvfb-run -a python3 classic_mouse_verify.py ./classic_graphics_test` in the same container printed `ClassicCanvas real mouse capture passed`.
- **Face check probe.** The Cairo face check was validated by a probe beforehand. For DejaVu Sans, Liberation Serif, "System" and an unknown family at 12, 13.5 and 20 pt, plain and bold, the runtime's width and height equalled the private Cairo context's ink extents for "Ag", "a", "Hello, wörld" and "ÅÉgj".
- **Not run.** macOS, Windows and arm64 Linux were not executed this wave (no GUI runs on shared desktops). Off Linux, the test asserts the explicit `UnsupportedOperationException` for the metric members.

## Upstream

No new defect was found, so this wave adds no record under `upstream-issues/classic-wave2-graphics`. Two existing records apply:

- The runtime's ink-width `MeasureStringWidth` and toy text are covered by BUI-002.
- The wrapper `NativeHandle` is covered by BUI-001.

The missing font-metric and synchronous-repaint APIs are enhancement gaps already listed in the installed `xojo-shim-gaps.md` (`TextHeight`, `TextAscent`, `DrawTextBlock`); they are not defects.

## Remaining core work

Independent Opus review found no blocking defect in this graphics wave. It
confirmed scale-2 pixel/cache behavior and the native mouse regression. Remaining
advisories: wrapping a native context changes its drawing colour and pen state;
mixing native drawing should restore those explicitly. ApplyMask replaces the
mask object, so reacquire Mask afterward. Equal/asymmetric geometry paths can
have discontinuous pixel coverage, including line caps and oversized corner
arcs; those policies still need a Xojo oracle. Grapheme handling is partial and
may split regional-indicator flags or tag sequences. Font calibration uses a
Picture context; Canvas hinting equivalence remains untested.

- A font-metrics API (ascent, descent, line height, advance) on every platform, so macOS and Windows can support TextAscent, TextHeight and wrapping.
- A replace/clear compositing mode or in-place pixel access, which would remove the cached rebuild.
- Synchronous canvas repaint, and dirty-rect reporting in `Paint`.
- A mouse/key injection hook, so the canvas bridge can be tested headlessly.
- Probing of asymmetric-pen, elliptical-corner and polygon geometry against real Xojo.
