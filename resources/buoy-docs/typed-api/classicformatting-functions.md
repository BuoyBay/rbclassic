---
title: "rbclassic \u00b7 ClassicFormatting functions"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: []
dependencies: []
symbols: ["ClassicCStr", "ClassicFormatMask"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicFormatting functions

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicFormatting functions

### ClassicCStr

`Public Function ClassicCStr(n As Double, loc As Locale) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `Double` | `ByVal` | Required |
| `loc` | `Locale` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ClassicCStr (overload 2)

`Public Function ClassicCStr(n As Double) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `Double` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ClassicCStr (overload 3)

`Public Function ClassicCStr(n As Single, loc As Locale) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `Single` | `ByVal` | Required |
| `loc` | `Locale` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ClassicCStr (overload 4)

`Public Function ClassicCStr(n As Single) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `Single` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ClassicCStr (overload 5)

`Public Function ClassicCStr(n As Integer) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ClassicCStr (overload 6)

`Public Function ClassicCStr(n As Integer, loc As Locale) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `Integer` | `ByVal` | Required |
| `loc` | `Locale` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ClassicCStr (overload 7)

`Public Function ClassicCStr(n As UInt64) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `UInt64` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ClassicCStr (overload 8)

`Public Function ClassicCStr(n As UInt64, loc As Locale) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `UInt64` | `ByVal` | Required |
| `loc` | `Locale` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ClassicCStr (overload 9)

`Public Function ClassicCStr(n As Boolean) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `Boolean` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ClassicCStr (overload 10)

`Public Function ClassicCStr(n As String) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ClassicCStr (overload 11)

`Public Function ClassicCStr(n As ClassicDate) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `ClassicDate` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ClassicCStr (overload 12)

`Public Function ClassicCStr(n As Variant, loc As Locale) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `Variant` | `ByVal` | Required |
| `loc` | `Locale` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ClassicCStr (overload 13)

`Public Function ClassicCStr(n As Variant) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `Variant` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ClassicFormatMask

`Public Function ClassicFormatMask(n As Double, mask As String) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `Double` | `ByVal` | Required |
| `mask` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ClassicFormatMask (overload 2)

`Public Function ClassicFormatMask(n As Double, mask As String, loc As Locale) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `Double` | `ByVal` | Required |
| `mask` | `String` | `ByVal` | Required |
| `loc` | `Locale` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ClassicFormatMask (overload 3)

`Public Function ClassicFormatMask(n As Integer, mask As String) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `Integer` | `ByVal` | Required |
| `mask` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ClassicFormatMask (overload 4)

`Public Function ClassicFormatMask(n As Integer, mask As String, loc As Locale) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `Integer` | `ByVal` | Required |
| `mask` | `String` | `ByVal` | Required |
| `loc` | `Locale` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ClassicFormatMask (overload 5)

`Public Function ClassicFormatMask(n As UInt64, mask As String) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `UInt64` | `ByVal` | Required |
| `mask` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ClassicFormatMask (overload 6)

`Public Function ClassicFormatMask(n As UInt64, mask As String, loc As Locale) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `UInt64` | `ByVal` | Required |
| `mask` | `String` | `ByVal` | Required |
| `loc` | `Locale` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |
