---
title: "rbclassic \u00b7 ClassicSystem functions"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: []
dependencies: []
symbols: ["ErrorCode", "Mode", "RouterHops", "SendToSelf", "System.IsFunctionAvailable", "System.Log", "Timer.ModeMultiple", "Timer.ModeOff", "Timer.ModeSingle"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicSystem functions

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicSystem functions

### Mode

`Public Extension Function Mode(t As Timer) As Integer`

Mode on a plain Timer reports the last RunMode/Enabled/Mode assignment. It cannot observe native Start/Stop or automatic one-shot completion. Use ClassicTimer when completion must update Mode (see notes/system.md).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `t` | `Timer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### Mode (overload 2)

`Public Extension Sub Mode(t As Timer, Assigns value As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `t` | `Timer` | `ByVal` | Required |
| `value` | `Integer` | `Assigns` | Required |

Returns: no value.

### Timer.ModeOff

`Public Extension Shared Function Timer.ModeOff() As Integer`

No parameters.

#### Returns

| Type |
| --- |
| `Integer` |

### Timer.ModeSingle

`Public Extension Shared Function Timer.ModeSingle() As Integer`

No parameters.

#### Returns

| Type |
| --- |
| `Integer` |

### Timer.ModeMultiple

`Public Extension Shared Function Timer.ModeMultiple() As Integer`

No parameters.

#### Returns

| Type |
| --- |
| `Integer` |

### ErrorCode

`Public Extension Function ErrorCode(sh As Shell) As Integer`

Most recent synchronous Execute status; native Shell remains persistent.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `sh` | `Shell` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### RouterHops

`Public Extension Sub RouterHops(socket As UDPSocket, Assigns value As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `socket` | `UDPSocket` | `ByVal` | Required |
| `value` | `Integer` | `Assigns` | Required |

Returns: no value.

### SendToSelf

`Public Extension Sub SendToSelf(socket As UDPSocket, Assigns value As Boolean)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `socket` | `UDPSocket` | `ByVal` | Required |
| `value` | `Boolean` | `Assigns` | Required |

Returns: no value.

### System.IsFunctionAvailable

`Public Extension Shared Function System.IsFunctionAvailable(functionName As String, libraryName As String) As Boolean`

Native exported-symbol lookup. Library paths/names follow the OS loader; c is additionally accepted on Unix, System on macOS. No symbol invocation.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `functionName` | `String` | `ByVal` | Required |
| `libraryName` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### System.Log

`Public Extension Shared Sub System.Log(level As Integer, message As String)`

POSIX-only integer-priority overload of the API 1 argument order. Accepts native syslog severities 0..7; no guessed legacy LogLevel constants. Requires /usr/bin/logger. Windows needs a real Event Log adapter.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `level` | `Integer` | `ByVal` | Required |
| `message` | `String` | `ByVal` | Required |

Returns: no value.
