---
title: "rbclassic \u00b7 ClassicShell"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicShell"]
dependencies: []
symbols: ["ClassicShell"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicShell

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicShell

`Public Class ClassicShell`

Rewrite Shell to ClassicShell for per-Execute processes and API 1 modes. UTF-8 pipes, no PTY; stdout/stderr ordering across pipes is not preserved. Async events need the native event loop or explicit Poll calls.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `Mode` | `Integer` | No | No | — | — |
| `TimeOut` | `Integer` | No | No | `2000` | Windows-only, as in API 1. -1 disables the timeout. |
| `Result` | `String` | Yes | No | — | — |
| `ErrorCode` | `Integer` | Yes | No | — | — |
| `ExitCode` | `Integer` | Yes | No | — | — |
| `IsRunning` | `Boolean` | Yes | No | — | — |

### DataAvailable

`Public Event DataAvailable()`

No parameters.

Returns: no value.

### Completed

`Public Event Completed()`

No parameters.

Returns: no value.

### Execute

`Public Sub Execute(command As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `command` | `String` | `ByVal` | Required |

Returns: no value.

### Poll

`Public Sub Poll()`

Poll observes real process status and pipe EOF; it does not infer completion from silence. Call on the main thread, like the native timer callback.

No parameters.

Returns: no value.

### ReadAll

`Public Function ReadAll() As String`

No parameters.

#### Returns

| Type |
| --- |
| `String` |

### Write

`Public Sub Write(data As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `data` | `String` | `ByVal` | Required |

Returns: no value.

### WriteLine

`Public Sub WriteLine(data As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `data` | `String` | `ByVal` | Required |

Returns: no value.

### Close

`Public Sub Close()`

No parameters.

Returns: no value.

### Destructor

`Public Sub Destructor()`

No parameters.

Returns: no value.
