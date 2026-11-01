---
title: "rbclassic \u00b7 ClassicSQLitePreparedStatement"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicSQLitePreparedStatement"]
dependencies: []
symbols: ["ClassicSQLitePreparedStatement"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicSQLitePreparedStatement

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicSQLitePreparedStatement

`Public Class ClassicSQLitePreparedStatement`

Reusable SQLite statement. Bind indexes are zero-based; missing binds fail. Binary APIs deliberately take Bytes rather than a lossy String/Variant.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `ParameterCount` | `Integer` | Yes | No | — | — |

### Constants

| Name | Type | Value / Default | Description |
| --- | --- | --- | --- |
| `SQLITE_INTEGER` | `Integer` | `1` | — |
| `SQLITE_DOUBLE` | `Integer` | `2` | — |
| `SQLITE_TEXT` | `Integer` | `3` | — |
| `SQLITE_BLOB` | `Integer` | `4` | — |
| `SQLITE_NULL` | `Integer` | `5` | — |
| `SQLITE_INT64` | `Integer` | `6` | — |
| `SQLITE_BOOLEAN` | `Integer` | `7` | — |

### Constructor

`Public Sub Constructor(owner As ClassicSQLiteDatabase, db As Ptr, sql As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `owner` | `ClassicSQLiteDatabase` | `ByVal` | Required |
| `db` | `Ptr` | `ByVal` | Required |
| `sql` | `String` | `ByVal` | Required |

Returns: no value.

### BindType

`Public Sub BindType(index As Integer, bindingType As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |
| `bindingType` | `Integer` | `ByVal` | Required |

Returns: no value.

### Bind

`Public Sub Bind(index As Integer, value As Variant)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |
| `value` | `Variant` | `ByVal` | Required |

Returns: no value.

### BindBlob

`Public Sub BindBlob(index As Integer, data As Bytes)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |
| `data` | `Bytes` | `ByVal` | Required |

Returns: no value.

### BindTextBytes

`Public Sub BindTextBytes(index As Integer, data As Bytes)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |
| `data` | `Bytes` | `ByVal` | Required |

Returns: no value.

### Reset

`Public Sub Reset(clearBindings As Boolean = False)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `clearBindings` | `Boolean` | `ByVal` | `False` |

Returns: no value.

### SQLSelect

`Public Function SQLSelect(ParamArray values As Variant) As RecordSet`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `values` | `Variant` | `ParamArray` | Required |

#### Returns

| Type |
| --- |
| `RecordSet` |

### SQLExecute

`Public Sub SQLExecute(ParamArray values As Variant)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `values` | `Variant` | `ParamArray` | Required |

Returns: no value.

### Close

`Public Sub Close()`

No parameters.

Returns: no value.

### Destructor

`Public Sub Destructor()`

No parameters.

Returns: no value.
