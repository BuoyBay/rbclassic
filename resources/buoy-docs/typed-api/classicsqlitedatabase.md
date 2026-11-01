---
title: "rbclassic \u00b7 ClassicSQLiteDatabase"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicSQLiteDatabase"]
dependencies: []
symbols: ["ClassicSQLiteDatabase"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicSQLiteDatabase

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicSQLiteDatabase

`Public Class ClassicSQLiteDatabase`

Boolean Connect and per-operation API 1 error state over checked SQLite. DatabaseFile Nil means an in-memory database. Connect(String) is an extension.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `ConnectionRevision` | `Integer` | Yes | No | — | — |
| `DatabaseFile` | `FolderItem` | No | No | — | — |
| `Error` | `Boolean` | Yes | No | — | — |
| `ErrorCode` | `Integer` | Yes | No | — | — |
| `ErrorMessage` | `String` | Yes | No | — | — |

### ClearError

`Public Sub ClearError()`

No parameters.

Returns: no value.

### SaveError

`Public Sub SaveError(e As Exception)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `e` | `Exception` | `ByVal` | Required |

Returns: no value.

### IsConnected

`Public Function IsConnected() As Boolean`

No parameters.

#### Returns

| Type |
| --- |
| `Boolean` |

### Connect

`Public Function Connect() As Boolean`

No parameters.

#### Returns

| Type |
| --- |
| `Boolean` |

### Connect (overload 2)

`Public Function Connect(filename As String) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `filename` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### CreateDatabase

`Public Function CreateDatabase() As Boolean`

No parameters.

#### Returns

| Type |
| --- |
| `Boolean` |

### Close

`Public Sub Close()`

No parameters.

Returns: no value.

### Destructor

`Public Sub Destructor()`

No parameters.

Returns: no value.

### Prepare

`Public Function Prepare(sql As String) As ClassicSQLitePreparedStatement`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `sql` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `ClassicSQLitePreparedStatement` |

### OpenEditableRecord

`Public Function OpenEditableRecord(tableName As String, primaryKey As String, key As Variant) As ClassicEditableRecord`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `tableName` | `String` | `ByVal` | Required |
| `primaryKey` | `String` | `ByVal` | Required |
| `key` | `Variant` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `ClassicEditableRecord` |

### Changes

`Public Function Changes() As Integer`

No parameters.

#### Returns

| Type |
| --- |
| `Integer` |

### TableSchema

`Public Function TableSchema(tableName As String) As RecordSet`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `tableName` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `RecordSet` |

### Tables

`Public Function Tables() As RecordSet`

No parameters.

#### Returns

| Type |
| --- |
| `RecordSet` |

### SQLSelect

`Public Function SQLSelect(sql As String, ParamArray values As Variant) As RecordSet`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `sql` | `String` | `ByVal` | Required |
| `values` | `Variant` | `ParamArray` | Required |

#### Returns

| Type |
| --- |
| `RecordSet` |

### SQLSelectBound

`Public Function SQLSelectBound(sql As String, values As Array Of Variant) As RecordSet`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `sql` | `String` | `ByVal` | Required |
| `values` | `Array Of Variant` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `RecordSet` |

### SQLExecute

`Public Sub SQLExecute(sql As String, ParamArray values As Variant)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `sql` | `String` | `ByVal` | Required |
| `values` | `Variant` | `ParamArray` | Required |

Returns: no value.

### SQLExecuteBound

`Public Sub SQLExecuteBound(sql As String, values As Array Of Variant)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `sql` | `String` | `ByVal` | Required |
| `values` | `Array Of Variant` | `ByVal` | Required |

Returns: no value.

### InsertRecord

`Public Sub InsertRecord(tableName As String, record As ClassicDatabaseRecord)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `tableName` | `String` | `ByVal` | Required |
| `record` | `ClassicDatabaseRecord` | `ByVal` | Required |

Returns: no value.

### InsertRecord (overload 2)

`Public Sub InsertRecord(tableName As String, row As DatabaseRow)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `tableName` | `String` | `ByVal` | Required |
| `row` | `DatabaseRow` | `ByVal` | Required |

Returns: no value.

### LastRowID

`Public Function LastRowID() As Integer`

No parameters.

#### Returns

| Type |
| --- |
| `Integer` |
