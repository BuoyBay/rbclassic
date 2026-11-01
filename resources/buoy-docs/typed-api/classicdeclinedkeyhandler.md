---
title: "rbclassic \u00b7 ClassicDeclinedKeyHandler"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicDeclinedKeyHandler"]
dependencies: []
symbols: ["ClassicDeclinedKeyHandler"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicDeclinedKeyHandler

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicDeclinedKeyHandler

`Public Interface ClassicDeclinedKeyHandler`

Window-level key handling for a key a focused list declined. API 1 raises the focused control's KeyDown before the window's Default/Cancel button acts, so a window-level handler (ClassicDesktop's push buttons) lets keys reach a focused list first and registers here to receive Return/Enter/Escape that the list's KeyDown did not consume. Return True when the key was used; the list then does not handle it natively.

### ClassicDeclinedKey

`Function ClassicDeclinedKey(listWidget As Ptr, keyval As Integer) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `listWidget` | `Ptr` | `ByVal` | Required |
| `keyval` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |
