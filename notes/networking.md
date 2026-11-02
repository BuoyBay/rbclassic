# ClassicAsyncNet — networking

## Exports and integration

The entry needs **`Public Import ClassicAsyncNet`**. The public classes are
`ClassicTCPSocket`, `ClassicHTTPSocket`, and `ClassicInternetHeaders`. There are
no exported ordinary functions requiring a selective import. Import RBFoundation as the
foundation; no ProcessKit, HTTPKit, crypto, or third-party networking package is
required. HTTPKit was inspected: its maintained surface is an HTTP server/router,
not a client transport or TLS foundation for this adapter.

Rewrite legacy source types explicitly:

- `TCPSocket` → `ClassicTCPSocket` for this client's asynchronous behavior.
- Classic `HTTPSocket` → `ClassicHTTPSocket` for the HTTP/1.0 adapter.
- Classic HTTP header parameter/storage types → `ClassicInternetHeaders`.

Do **not** map `Xojo.Net.HTTPSocket` to this class. Its event and protocol contracts
are different. Error handlers use Buoy `Exception` and its `ErrorCode`, rather
than assuming Xojo `RuntimeException.ErrorNumber` spelling is available.

Primary contract references: the [versioned TCPSocket reference](https://documentation.xojo.com/versions/2022r4/api/networking/tcpsocket.html)
and [deprecated classic HTTPSocket reference](https://documentation.xojo.com/versions/2022r4/api/deprecated/httpsocket.html).
The latter identifies the original class as an HTTP/1.0 client deprecated in
2019r1, with HeadersReceived and PageReceived events carrying headers. The
[TCPSocket send-event reference](https://docs.xojo.com/api/networking/tcpsocket.html#tcpsocket-sendprogress)
also documents progress cancellation. These references establish the selected
legacy surface, not complete compatibility of this partial implementation.

## TCP behavior

`Connect()` launches a detached POSIX resolver worker and immediately returns.
No DNS lookup or blocking connect is performed on the caller. `getaddrinfo`
answers are tried in resolver order using nonblocking sockets and zero-timeout
`poll`, including fallback when an earlier address refuses connection. Each
Connect starts a worker; there is no aggregate resolver worker pool or global
concurrency limit. Callers creating many connections must throttle attempts.
Closing an attempt does not cancel its OS resolver call.

`State` reports: 0 idle, 1 resolving, 2 connecting, 3 connected, 4 EOF/closed,
5 failed. `Address` and `Port` configure the next attempt. Unlike some legacy
implementations, **Port remains the requested remote port**; `LocalPort` exposes
the actual ephemeral port. `Handle`, `LocalAddress`, `LocalPort`, and
`RemoteAddress` reflect native state and are cleared by Close. IPv4 loopback and
hostname fallback are tested; IPv6 uses the POSIX resolver/socket implementation
but has no native execution acceptance in this wave.

Use the main-thread `Poll()` method in a console program. GUI programs can use
the native 10 ms Timer with their ordinary main event loop. Poll never waits for
network readiness. A call does at most one send and one receive, each at most
64 KiB, so an unready or slow peer does not stall the event loop.

`Write(String)` queues UTF-8 bytes, including while resolution/connection is in
progress. It never emits inline send completion. Each native queue has a 16 MiB
limit; an overfull send throws and leaves the existing queue intact. Receive
queue saturation pauses recv until the caller drains native input. This limit
does **not** cap total unread Buoy input: ReadBytes can move unread bytes into
SavedInput (including ReadBytes(0)), allowing native reads to resume while the
combined unread total grows. There is no global or aggregate unread-memory cap.
`BytesAvailable`
counts buffered unread input; `BytesLeftToSend` counts data not yet accepted by
the OS. `SendProgress(bytesSent, bytesLeft)` reports a real positive send chunk,
then `SendComplete(False)` occurs when the current queue drains. Completion is
OS acceptance, **not remote receipt or acknowledgement**. A fatal error with
unsent data emits Error and does not invent a successful completion.

Returning True from SendProgress, or calling `CancelSend()`, clears the queued
remainder and emits `SendComplete(True)` once, preserving the connection. Bytes
already accepted by the OS cannot be recalled. Writes appended before the queue
drains join that batch. Batch identities isolate callbacks: after CancelSend
completes a batch and its nested SendComplete queues a successor, a stale True
return from the original SendProgress cannot cancel or complete that successor.
An empty write has no completion event. `Flush()` makes
one nonblocking Poll; it does not wait for a slow peer.

`Connected` precedes input/progress callbacks. It observes an actual connected
state even if the peer immediately closes. `DataAvailable` follows actual recv
activity and leaves the data available for reads. Peer EOF produces Error code
102 after preceding input observations. Native syscall failures preserve errno;
resolver failure uses **adapter category 1001**, not a fabricated native errno or
complete Xojo error-code translation. Normalized 102 and 1001 are the only
compatibility mappings. A terminal error is delivered once. No connect timeout
or per-socket deadline is claimed; the caller may Close at its own deadline.

`ReadBytes`, `LookaheadBytes`, `Read`, `ReadAll`, and `Lookahead` expose the queue.
Lookahead copies without consuming. Byte reads preserve embedded NUL. String
reads support UTF8 (default), Latin1, ASCII, and WindowsANSI; invalid decoding
and embedded NUL throw **before consumption**. Use byte reads for other encodings
or arbitrary binary input. Binary Write(Bytes) is not implemented; String writes
explicitly reject NUL instead of silently truncating it. Negative read counts
throw. `Purge()` clears input only.

`Close()` is silent, idempotent, aborts the send queue, stops the timer, and
preserves unread input. The same instance may reconnect after Close, which
clears the old input. `Disconnect()` additionally emits Error(102). Closing a
pending resolver does not join/block on the resolver: the outstanding worker
holds its native allocation until resolution returns and cannot invoke Buoy
callbacks. Native fds have FD_CLOEXEC; SIGPIPE is suppressed per socket/send.
Destruction releases resources without user callbacks.

Callbacks may call Poll recursively (guarded), cancel, close, or replace the
connection. Generation checks prevent access to the freed/replaced descriptor.
The Poll guard is restored explicitly in Catch before rethrow, accommodating
known BUI-015. A thrown user callback interrupts that callback batch; undelivered
transitions are not replayed, and unread bytes remain inspectable.

## Classic HTTP behavior and boundaries

`Get`, `Post`, and `GetHeaders` start asynchronous HTTP/1.0 requests over the same
transport. `SetPostContent`, `SetRequestHeader`, and `ClearRequestHeaders`
configure requests. The adapter owns Host, Connection, Content-Length and
Transfer-Encoding request framing. Request header names/values and content
reject NUL and CR/LF injection. Field names must be nonempty ASCII tokens at
insertion and serialization; response field names are validated before framing
interpretation. Spaces/tabs around names are rejected rather than normalized.
The accepted token character set follows [RFC 9110 section 5.6.2](https://www.rfc-editor.org/rfc/rfc9110.html#section-5.6.2).
Field values are not otherwise a complete RFC validator.

`Connected`, `HeadersReceived`, `ReceiveProgress`, `SendProgress`, `PageReceived`,
and Error reflect native transport and parsed response activity. Request and
response headers use `ClassicInternetHeaders` (`AppendHeader`, `Name`, `Value`,
`ValueAt`, `Count`); Value lookup is case-insensitive and returns the first value.
`PageHeaders`, `HTTPStatusCode`, `ErrorCode`, and `IsConnected` expose observations.
HTTP SendProgress is a notification with no Boolean return: legacy code that
returns a cancellation flag needs adaptation. It does not provide the TCP
adapter's SendProgress cancellation contract. Close cancels the entire HTTP
request; per-send HTTP cancellation is not implemented.

Headers are assembled across recv boundaries, with a 64 KiB header limit. Bodies
complete at the verified Content-Length or actual EOF for close-delimited
responses. HEAD, 204 and 304 select bodyless framing before body-size checks or
receive progress. Their Content-Length metadata may exceed 16 MiB; it must still
be a valid decimal field. Any trailing wire bytes are discarded, the page is
empty, and no ReceiveProgress is emitted. A 404 is a completed HTTP
response, not a transport failure. Duplicate Content-Length, malformed status,
truncated declared body, unsupported transfer/content encoding and body NUL
produce Error and no PageReceived. Body buffering is limited to 16 MiB.
Connection resources are released before PageReceived, allowing a subsequent
request from that callback.

PageReceived content and ReceiveProgress newData map wire bytes through Latin1;
progress is cumulative byte count plus actual newly received body data, with -1
for unknown total. This models an eight-bit legacy String without pretending
Buoy has binary Strings. For UTF-8 content, explicitly recover the wire bytes
with `Bytes.FromString(content, Text.Encodings.Latin1)` and decode UTF8. HTTP
content containing NUL is rejected instead of reporting a truncated success.

Supported URLs are explicit lowercase `http://`, an ASCII hostname with optional
port, and an escaped ASCII slash path/query. Credentials, fragment identifiers,
IPv6 URL literals, query-only URLs without a slash, redirects, proxy/auth hooks,
cookies, form dictionaries, streaming/file downloads, synchronous timeout
variants, interim 1xx handling, chunked encoding and compression are not
implemented. HTTP/1.1 status lines are accepted only with supported response
framing. **TLS/https is rejected explicitly**, with no downgrade or encryption
claim. This class is not SSLSocket, Xojo.Net.HTTPSocket, or URLConnection.

TCP Listen/Accept/server sockets, NetworkInterface binding, orderly half-close,
ReadError/WriteError parity and complete legacy error mappings remain outside
this client expansion. UDP remains the existing ClassicSystem/Xojo foundation;
the adapter adds no UDP DNS or invented completion event.

## Native staging and targets

Linux x86_64 has native runtime coverage. Both Linux architectures and both
Darwin architectures use this POSIX helper source; verify each target natively. **Windows is unsupported**:
Connect throws UnsupportedOperationException and no Windows helper/import
library is supplied. Six-target semantic checking is not native ABI/link or
behavior acceptance; Windows consumers must not stage this as a supported native
socket implementation.

Build a helper for each native target using that target's C toolchain. Linux:

```sh
cc -std=c11 -Wall -Wextra -Werror -fPIC -shared -pthread \
  native/networking/classic_asyncnet.c \
  -o /TEMP/STAGE/libClassicAsyncNet.so
```

Darwin staging recipe (not executed here): use `-dynamiclib -pthread` and output
`libClassicAsyncNet.dylib` with install name `@rpath/libClassicAsyncNet.dylib`.
The six-target package builder should stage the matching native payload for
supported target slices, without mixing architectures. Keep the library beside
the consumer source/output or pass `-L/TEMP/STAGE` when linking. Buoy's Declare
library name is `ClassicAsyncNet`; the compiler copies the located native library
beside its output and uses the loader-relative runtime search path.
