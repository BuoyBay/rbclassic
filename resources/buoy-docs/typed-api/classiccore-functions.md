---
title: "rbclassic \u00b7 ClassicCore functions"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: []
dependencies: []
symbols: ["ClassicExtent", "ClassicFormat", "ClassicRedim", "ClassicReplace", "InStr", "Len", "Mid", "UBound"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicCore functions

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicCore functions

### Len

`Public Function Len(text As String) As Integer`

Classic character count (Unicode codepoints in Buoy).

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `text` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### Mid

`Public Function Mid(text As String, start As Integer) As String`

Classic one-based substring, with the native String.Mid boundary rules.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `text` | `String` | `ByVal` | Required |
| `start` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### Mid (overload 2)

`Public Function Mid(text As String, start As Integer, count As Integer) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `text` | `String` | `ByVal` | Required |
| `start` | `Integer` | `ByVal` | Required |
| `count` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### InStr

`Public Function InStr(text As String, target As String) As Integer`

Classic one-based search; zero means not found. ASCII case folding.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `text` | `String` | `ByVal` | Required |
| `target` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### InStr (overload 2)

`Public Function InStr(start As Integer, text As String, target As String) As Integer`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `start` | `Integer` | `ByVal` | Required |
| `text` | `String` | `ByVal` | Required |
| `target` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### UBound

`Public Extension Function UBound Of T(items As Array Of T) As Integer`

Last index of a one-dimensional array, including -1 for an empty array.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `items` | `Array Of T` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### ClassicExtent

`Public Function ClassicExtent(upperBound As Integer) As Integer`

Convert a classic inclusive upper bound into a Buoy extent.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `upperBound` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### ClassicRedim

`Public Extension Sub ClassicRedim Of T(items As Array Of T, upperBound As Integer)`

Resize a resizable one-dimensional array using a classic inclusive bound.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `items` | `Array Of T` | `ByVal` | Required |
| `upperBound` | `Integer` | `ByVal` | Required |

Returns: no value.

### ClassicReplace

`Public Function ClassicReplace(text As String, target As String, replacement As String) As String`

First-only replacement; an empty target leaves the source unchanged. Named explicitly because native String.Replace already means replace-all.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `text` | `String` | `ByVal` | Required |
| `target` | `String` | `ByVal` | Required |
| `replacement` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ClassicFormat

`Public Function ClassicFormat(number As Double, mask As String) As String`

Locale-sensitive numeric mask, using the bundled legacy mask subset. Explicit name avoids replacing the existing invariant foundation Format.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `number` | `Double` | `ByVal` | Required |
| `mask` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ClassicFormat (overload 2)

`Public Function ClassicFormat(number As Integer, mask As String) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `number` | `Integer` | `ByVal` | Required |
| `mask` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ClassicFormat (overload 3)

`Public Function ClassicFormat(number As Double, mask As String, loc As Locale) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `number` | `Double` | `ByVal` | Required |
| `mask` | `String` | `ByVal` | Required |
| `loc` | `Locale` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ClassicFormat (overload 4)

`Public Function ClassicFormat(number As Integer, mask As String, loc As Locale) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `number` | `Integer` | `ByVal` | Required |
| `mask` | `String` | `ByVal` | Required |
| `loc` | `Locale` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |
