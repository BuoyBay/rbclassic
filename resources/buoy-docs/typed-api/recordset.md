---
title: "rbclassic \u00b7 RecordSet"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["RecordSet"]
dependencies: []
symbols: ["RecordSet"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · RecordSet

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## RecordSet

`Public Class RecordSet`

Buffered read navigation, initially on the first row, or BOF and EOF if empty.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `BOF` | `Boolean` | Yes | No | — | — |
| `EOF` | `Boolean` | Yes | No | — | — |
| `FieldCount` | `Integer` | Yes | No | — | — |

### Constructor

`Public Sub Constructor(rows As RowSet)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `rows` | `RowSet` | `ByVal` | Required |

Returns: no value.

### RecordCount

`Public Function RecordCount() As Integer`

No parameters.

#### Returns

| Type |
| --- |
| `Integer` |

### IdxField

`Public Function IdxField(index As Integer) As DatabaseField`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `index` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `DatabaseField` |

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

### MoveNext

`Public Sub MoveNext()`

No parameters.

Returns: no value.

### MovePrevious

`Public Sub MovePrevious()`

No parameters.

Returns: no value.

### MoveFirst

`Public Sub MoveFirst()`

No parameters.

Returns: no value.

### MoveLast

`Public Sub MoveLast()`

No parameters.

Returns: no value.

### Close

`Public Sub Close()`

No parameters.

Returns: no value.

### Edit

`Public Sub Edit()`

No parameters.

Returns: no value.

### Update

`Public Sub Update()`

No parameters.

Returns: no value.

### DeleteRecord

`Public Sub DeleteRecord()`

No parameters.

Returns: no value.
