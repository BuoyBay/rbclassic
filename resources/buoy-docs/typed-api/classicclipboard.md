---
title: "rbclassic \u00b7 ClassicClipboard"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicClipboard"]
dependencies: []
symbols: ["ClassicClipboard"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicClipboard

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicClipboard

`Public Class ClassicClipboard`

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `IsClosed` | `Boolean` | Yes | No | — | — |
| `Text` | `String` | No | No | — | — |

### TextAvailable

`Public Function TextAvailable() As Boolean`

No parameters.

#### Returns

| Type |
| --- |
| `Boolean` |

### RawData

`Public Function RawData(dataType As String) As Bytes`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `dataType` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Bytes` |

### RawDataAvailable

`Public Function RawDataAvailable(dataType As String) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `dataType` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### RawData (overload 2)

`Public Sub RawData(dataType As String, Assigns value As Bytes)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `dataType` | `String` | `ByVal` | Required |
| `value` | `Bytes` | `Assigns` | Required |

Returns: no value.

### SetRawData

`Public Sub SetRawData(dataType As String, value As Bytes)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `dataType` | `String` | `ByVal` | Required |
| `value` | `Bytes` | `ByVal` | Required |

Returns: no value.

### Clear

`Public Sub Clear()`

No parameters.

Returns: no value.

### Cancel

`Public Sub Cancel()`

No parameters.

Returns: no value.

### Close

`Public Sub Close()`

No parameters.

Returns: no value.
