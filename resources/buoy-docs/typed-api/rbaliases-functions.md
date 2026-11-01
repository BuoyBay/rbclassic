---
title: "rbclassic \u00b7 RBAliases functions"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: []
dependencies: []
symbols: ["ArrayExtent", "KeyNameForMacKeyCode", "Lowercase", "Replace", "ShowMessageBox", "Uppercase"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · RBAliases functions

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## RBAliases functions

### Lowercase

`Public Function Lowercase(text As String) As String`

Readable casing helpers. Semantics are exactly Buoy String.LCase/UCase.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `text` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### Uppercase

`Public Function Uppercase(text As String) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `text` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### Replace

`Public Function Replace(text As String, target As String, replacement As String) As String`

Explicit first-only legacy replacement; native String.Replace defaults to all.

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

### ArrayExtent

`Public Function ArrayExtent(upperBound As Integer) As Integer`

Classic inclusive upper-bound conversion, suitable for New array extents.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `upperBound` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### ShowMessageBox

`Public Function ShowMessageBox(message As String) As Boolean`

Vendor-neutral spelling for the installed one-button compatibility dialog.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `message` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### KeyNameForMacKeyCode

`Public Function KeyNameForMacKeyCode(code As Integer) As KeyName`

Decode a hardware Mac key code without requiring a Mac host.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `code` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `KeyName` |
