---
title: "rbclassic \u00b7 ClassicFolderItem"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicFolderItem"]
dependencies: []
symbols: ["ClassicFolderItem"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicFolderItem

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicFolderItem

`Public Class ClassicFolderItem Inherits FolderItem`

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `LastErrorCode` | `Integer` | Yes | No | — | — |
| `NativeErrorCode` | `Integer` | Yes | No | — | — |

### Constructor

`Public Sub Constructor(aPath As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `aPath` | `String` | `ByVal` | Required |

Returns: no value.

### Constructor (overload 2)

`Public Sub Constructor(item As FolderItem)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `item` | `FolderItem` | `ByVal` | Required |

Returns: no value.

### Delete

`Public Sub Delete()`

No parameters.

Returns: no value.
