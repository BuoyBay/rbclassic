---
title: "rbclassic \u00b7 ClassicDatabaseRecord"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicDatabaseRecord"]
dependencies: []
symbols: ["ClassicDatabaseRecord"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicDatabaseRecord

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicDatabaseRecord

`Public Class ClassicDatabaseRecord`

DatabaseRecord collides with the stdlib ORM marker interface.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `FieldCount` | `Integer` | Yes | No | — | — |

### FieldName

`Public Function FieldName(index As Integer) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### Column

`Public Function Column(name As String) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `name` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### Column (overload 2)

`Public Function Column(index As Integer) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### Column (overload 3)

`Public Sub Column(name As String, Assigns value As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `name` | `String` | `ByVal` | Required |
| `value` | `String` | `Assigns` | Required |

Returns: no value.

### IntegerColumn

`Public Function IntegerColumn(name As String) As Integer`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `name` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### IntegerColumn (overload 2)

`Public Sub IntegerColumn(name As String, Assigns value As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `name` | `String` | `ByVal` | Required |
| `value` | `Integer` | `Assigns` | Required |

Returns: no value.

### Int64Column

`Public Function Int64Column(name As String) As Int64`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `name` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Int64` |

### Int64Column (overload 2)

`Public Sub Int64Column(name As String, Assigns value As Int64)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `name` | `String` | `ByVal` | Required |
| `value` | `Int64` | `Assigns` | Required |

Returns: no value.

### DoubleColumn

`Public Function DoubleColumn(name As String) As Double`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `name` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### DoubleColumn (overload 2)

`Public Sub DoubleColumn(name As String, Assigns value As Double)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `name` | `String` | `ByVal` | Required |
| `value` | `Double` | `Assigns` | Required |

Returns: no value.

### BooleanColumn

`Public Function BooleanColumn(name As String) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `name` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### BooleanColumn (overload 2)

`Public Sub BooleanColumn(name As String, Assigns value As Boolean)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `name` | `String` | `ByVal` | Required |
| `value` | `Boolean` | `Assigns` | Required |

Returns: no value.

### SetValue

`Public Sub SetValue(name As String, value As Variant)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `name` | `String` | `ByVal` | Required |
| `value` | `Variant` | `ByVal` | Required |

Returns: no value.

### ToDatabaseRow

`Public Function ToDatabaseRow() As DatabaseRow`

No parameters.

#### Returns

| Type |
| --- |
| `DatabaseRow` |
