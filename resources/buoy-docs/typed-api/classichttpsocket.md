---
title: "rbclassic \u00b7 ClassicHTTPSocket"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicHTTPSocket"]
dependencies: []
symbols: ["ClassicHTTPSocket"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicHTTPSocket

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicHTTPSocket

`Public Class ClassicHTTPSocket`

Classic HTTP/1.0 client, distinct from the foundation HTTPSocket and URLConnection. HTTP only. No silent TLS downgrade, redirects, proxy, chunking or compression.

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `RequestHeaders` | `ClassicInternetHeaders` | No | No | `New ClassicInternetHeaders()` | — |
| `HTTPStatusCode` | `Integer` | No | No | `0` | — |
| `ErrorCode` | `Integer` | No | No | `0` | — |
| `IsConnected` | `Boolean` | Yes | No | — | — |

### Connected

`Public Event Connected()`

No parameters.

Returns: no value.

### HeadersReceived

`Public Event HeadersReceived(headers As ClassicInternetHeaders, httpStatus As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `headers` | `ClassicInternetHeaders` | `ByVal` | Required |
| `httpStatus` | `Integer` | `ByVal` | Required |

Returns: no value.

### PageReceived

`Public Event PageReceived(url As String, httpStatus As Integer, headers As ClassicInternetHeaders, content As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `url` | `String` | `ByVal` | Required |
| `httpStatus` | `Integer` | `ByVal` | Required |
| `headers` | `ClassicInternetHeaders` | `ByVal` | Required |
| `content` | `String` | `ByVal` | Required |

Returns: no value.

### ReceiveProgress

`Public Event ReceiveProgress(bytesReceived As Integer, totalBytes As Integer, newData As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `bytesReceived` | `Integer` | `ByVal` | Required |
| `totalBytes` | `Integer` | `ByVal` | Required |
| `newData` | `String` | `ByVal` | Required |

Returns: no value.

### SendProgress

`Public Event SendProgress(bytesSent As Integer, bytesLeft As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `bytesSent` | `Integer` | `ByVal` | Required |
| `bytesLeft` | `Integer` | `ByVal` | Required |

Returns: no value.

### Error

`Public Event Error(e As Exception)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `e` | `Exception` | `ByVal` | Required |

Returns: no value.

### PageHeaders

`Public Function PageHeaders() As ClassicInternetHeaders`

No parameters.

#### Returns

| Type |
| --- |
| `ClassicInternetHeaders` |

### ClearRequestHeaders

`Public Sub ClearRequestHeaders()`

No parameters.

Returns: no value.

### SetRequestHeader

`Public Sub SetRequestHeader(name As String, value As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `name` | `String` | `ByVal` | Required |
| `value` | `String` | `ByVal` | Required |

Returns: no value.

### SetPostContent

`Public Sub SetPostContent(content As String, contentType As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `content` | `String` | `ByVal` | Required |
| `contentType` | `String` | `ByVal` | Required |

Returns: no value.

### Get

`Public Sub Get(url As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `url` | `String` | `ByVal` | Required |

Returns: no value.

### Post

`Public Sub Post(url As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `url` | `String` | `ByVal` | Required |

Returns: no value.

### GetHeaders

`Public Sub GetHeaders(url As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `url` | `String` | `ByVal` | Required |

Returns: no value.

### TransportConnected

`Public Sub TransportConnected()`

No parameters.

Returns: no value.

### TransportProgress

`Public Sub TransportProgress(sent As Integer, left As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `sent` | `Integer` | `ByVal` | Required |
| `left` | `Integer` | `ByVal` | Required |

Returns: no value.

### TransportData

`Public Sub TransportData()`

No parameters.

Returns: no value.

### TransportError

`Public Sub TransportError(e As Exception)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `e` | `Exception` | `ByVal` | Required |

Returns: no value.

### Poll

`Public Sub Poll()`

No parameters.

Returns: no value.

### Close

`Public Sub Close()`

No parameters.

Returns: no value.

### Destructor

`Public Sub Destructor()`

No parameters.

Returns: no value.
