---
title: "rbclassic \u00b7 ClassicUDPSocket"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicUDPSocket"]
dependencies: []
symbols: ["ClassicUDPSocket"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicUDPSocket

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicUDPSocket

`Public Class ClassicUDPSocket Inherits UDPSocket`

IPv4 API 1 Port/Connect facade. Inherited socket events are real native events. Close is terminal in Buoy; create another instance to reconnect.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `Port` | `Integer` | No | No | — | — |
| `IsConnected` | `Boolean` | Yes | No | — | — |

### Connect

`Public Sub Connect()`

No parameters.

Returns: no value.

### Write

`Public Sub Write(address As String, data As String)`

API 1 sends to this socket's Port, not the last peer's source port.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `address` | `String` | `ByVal` | Required |
| `data` | `String` | `ByVal` | Required |

Returns: no value.
