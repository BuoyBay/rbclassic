---
title: "rbclassic \u00b7 ClassicControlSets functions"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicControlSetHandler"]
dependencies: []
symbols: ["ClassicControlSetHandler"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicControlSets functions

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicControlSets functions

### ClassicControlSetHandler

`Public Closure Sub ClassicControlSetHandler(eventName As String, index As Integer)`

A handler for every event of a set, as an alternative to subclassing it: eventName is the API 1 event name ("Action", "Open", "Close", ...).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `eventName` | `String` | `ByVal` | Required |
| `index` | `Integer` | `ByVal` | Required |

Returns: no value.
