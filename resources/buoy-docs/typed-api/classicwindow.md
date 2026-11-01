---
title: "rbclassic \u00b7 ClassicWindow"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicWindow"]
dependencies: []
symbols: ["ClassicWindow"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicWindow

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicWindow

`Public Class ClassicWindow Inherits Window`

API 1 `Window`. Inherit this instead of Buoy's `Window` and keep API 1 event handler names. Event mapping: Open ← Opening; Close ← Closed (raised after the native close, so it cannot be cancelled — as in API 1); CancelClose(appQuitting) ← Closing; Activate/Deactivate ← Activated/Deactivated; Resizing/Resized ← Resized(finished False/True). Minimize/Maximize/Restore follow the native window state (Linux: GDK state notifications; Windows: WM_SIZE; macOS: re-read on Buoy's Shown/Hidden/Resized). Buoy's own window events are re-raised, so subclasses may still handle them. EnableMenuItems, window ConstructContextualMenu and KeyDown/Mouse*/Moved/Paint are not bridged (see notes). Window-level drops are not available: Buoy's Window is not a drop target, so Accept*Drop raises UnsupportedOperationException; accept drops on a control instead.
