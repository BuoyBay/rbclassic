---
title: "rbclassic \u00b7 ClassicInterop functions"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: []
dependencies: []
symbols: ["BoxClassicValue", "TryToVariant", "TryUnboxClassicValue"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicInterop functions

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicInterop functions

### TryToVariant

`Public Extension Function TryToVariant(value As ClassicVariant) As Optional Of Variant`

None when the foundation Variant cannot preserve this ClassicVariant kind.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `ClassicVariant` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Optional Of Variant` |

### BoxClassicValue

`Public Function BoxClassicValue(value As ClassicVariant) As Variant`

Explicit object boxing preserves extended payloads without scalar coercion.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `ClassicVariant` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Variant` |

### TryUnboxClassicValue

`Public Function TryUnboxClassicValue(value As Variant) As Optional Of ClassicVariant`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `Variant` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Optional Of ClassicVariant` |
