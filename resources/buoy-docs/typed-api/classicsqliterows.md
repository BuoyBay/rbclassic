---
title: "rbclassic \u00b7 ClassicSQLiteRows"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicSQLiteRows"]
dependencies: []
symbols: ["ClassicSQLiteRows"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicSQLiteRows

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicSQLiteRows

`Class ClassicSQLiteRows Inherits RowSet`

### Constructor

`Public Sub Constructor(db As Ptr, stmt As Ptr, borrowed As Boolean = False)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `db` | `Ptr` | `ByVal` | Required |
| `stmt` | `Ptr` | `ByVal` | Required |
| `borrowed` | `Boolean` | `ByVal` | `False` |

Returns: no value.

### HasMoreRows

`Public Overrides Function HasMoreRows() As Boolean`

No parameters.

#### Returns

| Type |
| --- |
| `Boolean` |

### NextRow

`Public Overrides Sub NextRow()`

No parameters.

Returns: no value.

### ColumnCount

`Public Overrides Function ColumnCount() As Integer`

No parameters.

#### Returns

| Type |
| --- |
| `Integer` |

### ColumnName

`Public Overrides Function ColumnName(index As Integer) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### Value

`Public Overrides Function Value(column As String) As DbValue`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `column` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `DbValue` |

### Value (overload 2)

`Public Overrides Function Value(index As Integer) As DbValue`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `DbValue` |

### Snapshot

`Public Function Snapshot(index As Integer) As DatabaseField`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `DatabaseField` |

### Close

`Public Overrides Sub Close()`

No parameters.

Returns: no value.

### Destructor

`Public Sub Destructor()`

No parameters.

Returns: no value.
