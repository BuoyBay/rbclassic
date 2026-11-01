---
title: "rbclassic \u00b7 ClassicFiles functions"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: []
dependencies: []
symbols: ["ClearClassicFileTypes", "CreateTextFile", "Directory", "FolderItem.PathTypeAbsolute", "FolderItem.PathTypeNative", "FolderItem.PathTypeShell", "FolderItem.PathTypeURL", "GetFolderItem", "GetOpenFolderItem", "GetSaveFolderItem", "GetTemporaryFolderItem", "Item", "OpenAsTextFile", "Read", "ReadInt8", "ReadPString", "ReadPStringBytes", "ReadUInt8", "RegisterClassicFileType", "ResolveClassicFileTypes", "ResolveSymbolicLinks", "SelectFolder", "SetModificationDateTime", "SpecialFolder.Movies", "SpecialFolder.Music", "SpecialFolder.Pictures", "Write", "WriteInt8", "WritePString", "WriteUInt8"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicFiles functions

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicFiles functions

### FolderItem.PathTypeAbsolute

`Public Extension Shared Function FolderItem.PathTypeAbsolute() As Integer`

No parameters.

#### Returns

| Type |
| --- |
| `Integer` |

### FolderItem.PathTypeShell

`Public Extension Shared Function FolderItem.PathTypeShell() As Integer`

No parameters.

#### Returns

| Type |
| --- |
| `Integer` |

### FolderItem.PathTypeURL

`Public Extension Shared Function FolderItem.PathTypeURL() As Integer`

No parameters.

#### Returns

| Type |
| --- |
| `Integer` |

### FolderItem.PathTypeNative

`Public Extension Shared Function FolderItem.PathTypeNative() As Integer`

No parameters.

#### Returns

| Type |
| --- |
| `Integer` |

### GetFolderItem

`Public Function GetFolderItem(aPath As String = "", pathMode As Integer = 0) As FolderItem`

Empty and relative paths are relative to the executable/bundle directory. Alias files and shortcuts are NOT resolved by the foundation.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `aPath` | `String` | `ByVal` | `""` |
| `pathMode` | `Integer` | `ByVal` | `0` |

#### Returns

| Type |
| --- |
| `FolderItem` |

### GetTemporaryFolderItem

`Public Function GetTemporaryFolderItem() As FolderItem`

No parameters.

#### Returns

| Type |
| --- |
| `FolderItem` |

### RegisterClassicFileType

`Public Sub RegisterClassicFileType(name As String, value As FileType)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `name` | `String` | `ByVal` | Required |
| `value` | `FileType` | `ByVal` | Required |

Returns: no value.

### ClearClassicFileTypes

`Public Sub ClearClassicFileTypes()`

No parameters.

Returns: no value.

### ResolveClassicFileTypes

`Public Function ResolveClassicFileTypes(filter As String) As Array Of FileType`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `filter` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Array Of FileType` |

### GetOpenFolderItem

`Public Function GetOpenFolderItem(filter As String) As FolderItem`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `filter` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `FolderItem` |

### GetOpenFolderItem (overload 2)

`Public Function GetOpenFolderItem(filter As FileType) As FolderItem`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `filter` | `FileType` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `FolderItem` |

### GetSaveFolderItem

`Public Function GetSaveFolderItem(filter As String, defaultName As String) As FolderItem`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `filter` | `String` | `ByVal` | Required |
| `defaultName` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `FolderItem` |

### GetSaveFolderItem (overload 2)

`Public Function GetSaveFolderItem(filter As FileType, defaultName As String) As FolderItem`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `filter` | `FileType` | `ByVal` | Required |
| `defaultName` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `FolderItem` |

### SelectFolder

`Public Function SelectFolder() As FolderItem`

No parameters.

#### Returns

| Type |
| --- |
| `FolderItem` |

### Directory

`Public Extension Function Directory(item As FolderItem) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `item` | `FolderItem` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### Item

`Public Extension Function Item(folder As FolderItem, index As Integer) As FolderItem`

One-based; invalid index, non-directory, missing/unlistable path => Nil. Native symlinks follow OS behavior; Finder aliases/.lnk are unresolved.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `folder` | `FolderItem` | `ByVal` | Required |
| `index` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `FolderItem` |

### OpenAsTextFile

`Public Extension Function OpenAsTextFile(item As FolderItem) As TextInputStream`

Legacy Nil-on-open-failure equivalent; UTF-8, with no encoding sniffing.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `item` | `FolderItem` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `TextInputStream` |

### CreateTextFile

`Public Extension Function CreateTextFile(item As FolderItem) As TextOutputStream`

Creates/truncates; Nil on failure. Does not set Mac type/creator metadata.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `item` | `FolderItem` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `TextOutputStream` |

### ResolveSymbolicLinks

`Public Extension Function ResolveSymbolicLinks(item As FolderItem) As FolderItem`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `item` | `FolderItem` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `FolderItem` |

### SpecialFolder.Pictures

`Public Extension Shared Function SpecialFolder.Pictures() As FolderItem`

No parameters.

#### Returns

| Type |
| --- |
| `FolderItem` |

### SpecialFolder.Music

`Public Extension Shared Function SpecialFolder.Music() As FolderItem`

No parameters.

#### Returns

| Type |
| --- |
| `FolderItem` |

### SpecialFolder.Movies

`Public Extension Shared Function SpecialFolder.Movies() As FolderItem`

No parameters.

#### Returns

| Type |
| --- |
| `FolderItem` |

### ReadUInt8

`Public Extension Function ReadUInt8(stream As BinaryStream) As UInt8`

Raw one-byte unsigned read. EOF/short read returns zero, as in legacy.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `stream` | `BinaryStream` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `UInt8` |

### ReadInt8

`Public Extension Function ReadInt8(stream As BinaryStream) As Int8`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `stream` | `BinaryStream` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Int8` |

### WriteUInt8

`Public Extension Sub WriteUInt8(stream As BinaryStream, value As UInt8)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `stream` | `BinaryStream` | `ByVal` | Required |
| `value` | `UInt8` | `ByVal` | Required |

Returns: no value.

### WriteInt8

`Public Extension Sub WriteInt8(stream As BinaryStream, value As Int8)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `stream` | `BinaryStream` | `ByVal` | Required |
| `value` | `Int8` | `ByVal` | Required |

Returns: no value.

### ReadPStringBytes

`Public Extension Function ReadPStringBytes(stream As BinaryStream) As Bytes`

One-byte length followed by raw bytes; consumes short payload, returns empty.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `stream` | `BinaryStream` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Bytes` |

### ReadPString

`Public Extension Function ReadPString(stream As BinaryStream) As String`

Buoy cannot represent a Nil-encoded String: require explicit decoding.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `stream` | `BinaryStream` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ReadPString (overload 2)

`Public Extension Function ReadPString(stream As BinaryStream, encoding As TextEncoding) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `stream` | `BinaryStream` | `ByVal` | Required |
| `encoding` | `TextEncoding` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### WritePString

`Public Extension Sub WritePString(stream As BinaryStream, value As Bytes)`

Reject oversized values before writing anything; never split UTF-8 bytes.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `stream` | `BinaryStream` | `ByVal` | Required |
| `value` | `Bytes` | `ByVal` | Required |

Returns: no value.

### WritePString (overload 2)

`Public Extension Sub WritePString(stream As BinaryStream, value As String)`

Buoy strings always encode as UTF-8; prefix counts bytes, not characters.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `stream` | `BinaryStream` | `ByVal` | Required |
| `value` | `String` | `ByVal` | Required |

Returns: no value.

### Read

`Public Extension Function Read(stream As BinaryStream, count As Integer, encoding As TextEncoding) As String`

Explicit text decoding overload; Read(count) remains the native Bytes API.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `stream` | `BinaryStream` | `ByVal` | Required |
| `count` | `Integer` | `ByVal` | Required |
| `encoding` | `TextEncoding` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### Write

`Public Extension Sub Write(stream As BinaryStream, value As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `stream` | `BinaryStream` | `ByVal` | Required |
| `value` | `String` | `ByVal` | Required |

Returns: no value.

### SetModificationDateTime

`Public Extension Sub SetModificationDateTime(item As FolderItem, instant As DateTime)`

Sets modification time with millisecond precision, preserving access time. Creation-time mutation and legacy Date objects are outside this adapter.

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `item` | `FolderItem` | `ByVal` | Required |
| `instant` | `DateTime` | `ByVal` | Required |

Returns: no value.
