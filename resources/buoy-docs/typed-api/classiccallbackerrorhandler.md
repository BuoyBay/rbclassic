---
title: "rbclassic \u00b7 ClassicCallbackErrorHandler"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicCallbackErrorHandler"]
dependencies: []
symbols: ["ClassicCallbackErrorHandler"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicCallbackErrorHandler

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicCallbackErrorHandler

`Public Interface ClassicCallbackErrorHandler`

Receives exceptions raised by event handlers that ClassicDesktop invoked from a native callback. `origin` names the callback. Return True when handled; False lets the exception continue as an uncaught exception.

### CallbackError

`Function CallbackError(e As Exception, origin As String) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `e` | `Exception` | `ByVal` | Required |
| `origin` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |
