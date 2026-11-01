---
title: "rbclassic \u00b7 DatabaseField"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["DatabaseField"]
dependencies: []
symbols: ["DatabaseField"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · DatabaseField

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## DatabaseField

`Public Class DatabaseField`

Read-only scalar/binary snapshot. SQLite metadata is explicit; legacy Type codes are not inferred.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `SQLiteStorageType` | `Integer` | Yes | No | — | — |
| `DeclaredType` | `String` | Yes | No | — | — |
| `IsNull` | `Boolean` | Yes | No | — | — |
| `NativeBytes` | `Bytes` | Yes | No | — | — |
| `BlobBytes` | `Bytes` | Yes | No | — | — |
| `Name` | `String` | Yes | No | — | — |
| `Value` | `Variant` | Yes | No | — | — |
| `StringValue` | `String` | Yes | No | — | — |
| `IntegerValue` | `Integer` | Yes | No | — | — |
| `Int64Value` | `Int64` | Yes | No | — | — |
| `DoubleValue` | `Double` | Yes | No | — | — |
| `BooleanValue` | `Boolean` | Yes | No | — | — |

### Constructor

`Public Sub Constructor(column As DatabaseColumn, storageType As Integer, raw As Bytes, declaredType As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `column` | `DatabaseColumn` | `ByVal` | Required |
| `storageType` | `Integer` | `ByVal` | Required |
| `raw` | `Bytes` | `ByVal` | Required |
| `declaredType` | `String` | `ByVal` | Required |

Returns: no value.

### Constructor (overload 2)

`Public Sub Constructor(column As DatabaseColumn)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `column` | `DatabaseColumn` | `ByVal` | Required |

Returns: no value.

### GetString

`Public Function GetString() As String`

No parameters.

#### Returns

| Type |
| --- |
| `String` |
