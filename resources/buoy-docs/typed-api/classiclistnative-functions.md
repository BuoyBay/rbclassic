---
title: "rbclassic \u00b7 ClassicListNative functions"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: []
dependencies: []
symbols: ["ClassicListNativeOwnsKeys", "ClassicListNativeSetDeclinedKeyHandler"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicListNative functions

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicListNative functions

### ClassicListNativeSetDeclinedKeyHandler

`Public Sub ClassicListNativeSetDeclinedKeyHandler(handler As ClassicDeclinedKeyHandler)`

Installs (Nil removes) the handler for Return/Enter/Escape a focused native list declined. One handler; a later call replaces it.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `handler` | `ClassicDeclinedKeyHandler` | `ByVal` | Required |

Returns: no value.

### ClassicListNativeOwnsKeys

`Public Function ClassicListNativeOwnsKeys(focus As Ptr) As Boolean`

True when `focus` (a native focus widget) is inside an attached list, so the list's KeyDown sees keys before any window-level handler should act. Always False where the bridge is not implemented (macOS, Windows).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `focus` | `Ptr` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |
