---
title: "rbclassic \u00b7 ClassicInternetHeaders"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicInternetHeaders"]
dependencies: []
symbols: ["ClassicInternetHeaders"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicInternetHeaders

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicInternetHeaders

`Public Class ClassicInternetHeaders`

API 1-style headers; explicitly named because legacy ships no InternetHeaders.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `Count` | `Integer` | Yes | No | — | — |

### AppendHeader

`Public Sub AppendHeader(name As String, value As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `name` | `String` | `ByVal` | Required |
| `value` | `String` | `ByVal` | Required |

Returns: no value.

### Name

`Public Function Name(index As Integer) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### Value

`Public Function Value(name As String) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `name` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ValueAt

`Public Function ValueAt(index As Integer) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |
