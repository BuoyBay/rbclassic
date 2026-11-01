---
title: "rbclassic \u00b7 ClassicTCPSocket"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicTCPSocket"]
dependencies: []
symbols: ["ClassicTCPSocket"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicTCPSocket

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicTCPSocket

`Public Class ClassicTCPSocket`

Main-thread client. Poll explicitly in console programs; GUI uses Timer.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `Address` | `String` | No | No | `""` | — |
| `Port` | `Integer` | No | No | `0` | — |
| `LastErrorCode` | `Integer` | No | No | `0` | — |
| `State` | `Integer` | Yes | No | — | 0 idle, 1 resolving, 2 connecting, 3 connected, 4 EOF/closed, 5 failed. |
| `IsConnected` | `Boolean` | Yes | No | — | — |
| `BytesAvailable` | `Integer` | Yes | No | — | — |
| `BytesLeftToSend` | `Integer` | Yes | No | — | — |
| `Handle` | `Integer` | Yes | No | — | — |
| `LocalPort` | `Integer` | Yes | No | — | — |
| `LocalAddress` | `String` | Yes | No | — | — |
| `RemoteAddress` | `String` | Yes | No | — | — |

### Connected

`Public Event Connected()`

No parameters.

Returns: no value.

### DataAvailable

`Public Event DataAvailable()`

No parameters.

Returns: no value.

### Error

`Public Event Error(e As Exception)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `e` | `Exception` | `ByVal` | Required |

Returns: no value.

### SendProgress

`Public Event SendProgress(bytesSent As Integer, bytesLeft As Integer) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `bytesSent` | `Integer` | `ByVal` | Required |
| `bytesLeft` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### SendComplete

`Public Event SendComplete(userAborted As Boolean)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `userAborted` | `Boolean` | `ByVal` | Required |

Returns: no value.

### Connect

`Public Sub Connect()`

No parameters.

Returns: no value.

### Write

`Public Sub Write(data As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `data` | `String` | `ByVal` | Required |

Returns: no value.

### Poll

`Public Sub Poll()`

Nonblocking: completion means accepted by OS, not acknowledged by peer.

No parameters.

Returns: no value.

### LookaheadBytes

`Public Function LookaheadBytes() As Bytes`

No parameters.

#### Returns

| Type |
| --- |
| `Bytes` |

### ReadBytes

`Public Function ReadBytes(count As Integer) As Bytes`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `count` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Bytes` |

### Lookahead

`Public Function Lookahead(encoding As Text.Encodings = Text.Encodings.UTF8) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `encoding` | `Text.Encodings` | `ByVal` | `Text.Encodings.UTF8` |

#### Returns

| Type |
| --- |
| `String` |

### Read

`Public Function Read(count As Integer, encoding As Text.Encodings = Text.Encodings.UTF8) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `count` | `Integer` | `ByVal` | Required |
| `encoding` | `Text.Encodings` | `ByVal` | `Text.Encodings.UTF8` |

#### Returns

| Type |
| --- |
| `String` |

### ReadAll

`Public Function ReadAll(encoding As Text.Encodings = Text.Encodings.UTF8) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `encoding` | `Text.Encodings` | `ByVal` | `Text.Encodings.UTF8` |

#### Returns

| Type |
| --- |
| `String` |

### Purge

`Public Sub Purge()`

No parameters.

Returns: no value.

### CancelSend

`Public Sub CancelSend()`

No parameters.

Returns: no value.

### Flush

`Public Sub Flush()`

No parameters.

Returns: no value.

### EndOfFile

`Public Function EndOfFile() As Boolean`

No parameters.

#### Returns

| Type |
| --- |
| `Boolean` |

### Close

`Public Sub Close()`

No parameters.

Returns: no value.

### Disconnect

`Public Sub Disconnect()`

No parameters.

Returns: no value.

### Destructor

`Public Sub Destructor()`

No parameters.

Returns: no value.
