---
title: "rbclassic \u00b7 ClassicEncoding"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicEncoding"]
dependencies: []
symbols: ["ClassicEncoding"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicEncoding

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicEncoding

`Public Class ClassicEncoding`

### Constructor

`Public Sub Constructor(encodingName As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `encodingName` | `String` | `ByVal` | Required |

Returns: no value.

### DecodeBytes

`Public Function DecodeBytes(raw As Bytes) As Bytes`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `raw` | `Bytes` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Bytes` |

### Decode

`Public Function Decode(raw As Bytes) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `raw` | `Bytes` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### EncodeBytes

`Public Function EncodeBytes(utf8 As Bytes) As Bytes`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `utf8` | `Bytes` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Bytes` |

### Encode

`Public Function Encode(value As String) As Bytes`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Bytes` |
