---
title: "rbclassic \u00b7 Serial"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["Serial"]
dependencies: []
symbols: ["Serial"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · Serial

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## Serial

`Public Class Serial`

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `Baud` | `Integer` | No | No | `8` | — |
| `Bits` | `Integer` | No | No | `3` | — |
| `Parity` | `Integer` | No | No | `0` | — |
| `Stop` | `Integer` | No | No | `0` | — |
| `CTS` | `Boolean` | No | No | `False` | — |
| `XON` | `Boolean` | No | No | `False` | — |
| `LastErrorCode` | `Integer` | No | No | `0` | — |
| `NativeErrorCode` | `Integer` | No | No | `0` | — |
| `SerialPort` | `SerialPort` | No | No | — | — |
| `DevicePath` | `String` | No | No | `""` | — |
| `IsOpen` | `Boolean` | Yes | No | — | — |
| `BytesAvailable` | `Integer` | Yes | No | — | — |
| `DataTerminalReady` | `Boolean` | No | No | — | — |
| `RequestToSend` | `Boolean` | No | No | — | — |

### Constants

| Name | Type | Value / Default | Description |
| --- | --- | --- | --- |
| `Baud300` | `Integer` | `0` | — |
| `Baud600` | `Integer` | `1` | — |
| `Baud1200` | `Integer` | `2` | — |
| `Baud1800` | `Integer` | `3` | — |
| `Baud2400` | `Integer` | `4` | — |
| `Baud3600` | `Integer` | `5` | — |
| `Baud4800` | `Integer` | `6` | — |
| `Baud7200` | `Integer` | `7` | — |
| `Baud9600` | `Integer` | `8` | — |
| `Baud14400` | `Integer` | `9` | — |
| `Baud19200` | `Integer` | `10` | — |
| `Baud28800` | `Integer` | `11` | — |
| `Baud38400` | `Integer` | `12` | — |
| `Baud57600` | `Integer` | `13` | — |
| `Baud115200` | `Integer` | `14` | — |
| `Baud230400` | `Integer` | `15` | — |
| `Bits5` | `Integer` | `0` | — |
| `Bits6` | `Integer` | `1` | — |
| `Bits7` | `Integer` | `2` | — |
| `Bits8` | `Integer` | `3` | — |
| `ParityNone` | `Integer` | `0` | — |
| `ParityOdd` | `Integer` | `1` | — |
| `ParityEven` | `Integer` | `2` | — |
| `StopBits1` | `Integer` | `0` | — |
| `StopBits15` | `Integer` | `1` | — |
| `StopBits2` | `Integer` | `2` | — |
| `NoError` | `Integer` | `0` | — |
| `AccessDenied` | `Integer` | `100` | — |
| `PortNotFound` | `Integer` | `101` | — |
| `InvalidOptions` | `Integer` | `102` | — |

### Constructor

`Public Sub Constructor()`

No parameters.

Returns: no value.

### Open

`Public Function Open() As Boolean`

No parameters.

#### Returns

| Type |
| --- |
| `Boolean` |

### Close

`Public Sub Close()`

No parameters.

Returns: no value.

### EndOfFile

`Public Function EndOfFile() As Boolean`

No parameters.

#### Returns

| Type |
| --- |
| `Boolean` |

### LookAheadBytes

`Public Function LookAheadBytes() As Bytes`

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

### ReadAllBytes

`Public Function ReadAllBytes() As Bytes`

No parameters.

#### Returns

| Type |
| --- |
| `Bytes` |

### LookAhead

`Public Function LookAhead(encoding As Text.Encodings = Text.Encodings.UTF8) As String`

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

### Write

`Public Sub Write(data As Bytes)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `data` | `Bytes` | `ByVal` | Required |

Returns: no value.

### Write (overload 2)

`Public Sub Write(data As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `data` | `String` | `ByVal` | Required |

Returns: no value.
