---
title: "rbclassic \u00b7 ClassicEditableRecord"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicEditableRecord"]
dependencies: []
symbols: ["ClassicEditableRecord"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicEditableRecord

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicEditableRecord

`Public Class ClassicEditableRecord`

Single-use edit session for a named table and schema-verified scalar primary key. Changes are staged explicitly; each Update/Delete is one atomic SQLite statement.

### Constructor

`Public Sub Constructor(owner As ClassicSQLiteDatabase, tableName As String, primaryKey As String, key As Variant, snapshot As RecordSet)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `owner` | `ClassicSQLiteDatabase` | `ByVal` | Required |
| `tableName` | `String` | `ByVal` | Required |
| `primaryKey` | `String` | `ByVal` | Required |
| `key` | `Variant` | `ByVal` | Required |
| `snapshot` | `RecordSet` | `ByVal` | Required |

Returns: no value.

### Field

`Public Function Field(name As String) As DatabaseField`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `name` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `DatabaseField` |

### SetValue

`Public Sub SetValue(name As String, value As Variant)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `name` | `String` | `ByVal` | Required |
| `value` | `Variant` | `ByVal` | Required |

Returns: no value.

### Update

`Public Sub Update()`

No parameters.

Returns: no value.

### DeleteRecord

`Public Sub DeleteRecord()`

No parameters.

Returns: no value.

### Close

`Public Sub Close()`

No parameters.

Returns: no value.
