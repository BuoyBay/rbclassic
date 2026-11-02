# API 1 Serial scope

`modules/ClassicSerial.bui` exports the `Serial` class over installed
`serialio` 1.0.0's public `SerialConnection` API. It imports `Xojo` and
`Serialio.Serial`, never the RBClassic entry. The entry module exports it with
`Public Import ClassicSerial`; there are no global functions needing a selective
import. Callers constructing/enumerating native port descriptors should also
`Import Serialio.Serial` and use `SerialPort.GetPorts()`.

Implemented roadmap subset: ordinal configuration; Boolean `Open` and synchronous
error reporting; port-descriptor/device-path selection; real buffered byte I/O;
non-consuming lookahead; partial reads; explicit close/reopen; output DTR/RTS
line operations through the backend. This does not finish every Serial roadmap
item or establish full framework parity.

## Compatibility contract

The primary reference is the archived [Xojo API 1 Serial documentation, 2022r3](https://documentation.xojo.com/versions/2022r3/api/deprecated/serial.html),
particularly its Baud, Bits, Parity, Stop, LastErrorCode, Open, LookAhead and Read
sections. Values below are legacy ordinals, not raw hardware values:

| Configuration | Ordinals |
| --- | --- |
| Baud | 0–15 map to 300, 600, 1200, 1800, 2400, 3600, 4800, 7200, 9600, 14400, 19200, 28800, 38400, 57600, 115200, 230400 |
| Bits | 0–3 map to 5–8 bits; `Bits8 = 3` |
| Parity | None=0, Odd=1, Even=2 |
| Stop | One=0, OnePointFive=1, Two=2 |

`Baud9600 = 8`. Configurations default to 9600/8N1 without flow control.
`CTS` selects real RTS/CTS flow control and `XON` selects real XON/XOFF. Combining
both is rejected because this backend exposes mutually exclusive flow modes.
Invalid ordinals are rejected before native open. POSIX 1.5 stop bits are rejected
rather than silently approximated. Hardware support for other valid settings
remains the OS/driver's responsibility.

Set `SerialPort` to a native descriptor. The `DevicePath` extension, when nonempty,
takes precedence and can select a PTY or device omitted from enumeration.
`Open()` returns False on configuration/device/open failures and records
`LastErrorCode`; a repeated Open on an open connection returns True. Configuration
changes apply on the next successful open, not immediately.

Legacy error constants implemented: NoError=0, AccessDenied=100,
PortNotFound=101, InvalidOptions=102. Known native errors map to those constants;
other native errors retain their native number. `NativeErrorCode` preserves the
original synchronous native open/write error. Each fresh open attempt resets both
error fields. `LastErrorCode` is writable as in Xojo. A closed write throws
`IOException` and sets a nonzero local error (9); it does not represent a new
native operation. Other validation/decoding errors throw their corresponding
Buoy exception. Asynchronous read errors are not translated into LastErrorCode;
`IsOpen` reflects the backend connection state.

`BytesAvailable` collects the native receive buffer, reporting bytes, not
characters. Reads return up to the requested count without waiting for more.
`LookAheadBytes` returns an independent copy; changing it cannot modify unread
input. `ReadBytes`, `ReadAllBytes`, and `Write(Bytes)` preserve all byte values,
including NUL and 0xff. Counts must be nonnegative. Close discards facade unread
data and closes the native connection; another Open uses a fresh connection.

`Read`, `ReadAll`, and `LookAhead` return decoded strings, default UTF-8, with
explicit UTF8/ASCII/Latin1/WindowsANSI selectors also accepted. Xojo's
TextEncoding/Nil metadata model is not emulated. Other selectors are rejected;
use Bytes and decode explicitly. Because Buoy String cannot preserve embedded
NUL, string reads reject NUL-containing input **before consumption**. Invalid or
split UTF-8 likewise leaves the bytes available for a later read. Read counts are
byte counts; e.g. the UTF-8 character é requires two bytes. `Write(String)` encodes
UTF-8; binary data must use Bytes. `EndOfFile()` means the receive buffer is empty,
not that the peer disconnected.

`DataTerminalReady` forwards native DTR output state, and `RequestToSend` forwards
native RTS output state. These operate immediately, unlike API 1's queued Reset
semantics, and throw when closed. The backend has no separate error result for
line operations, so successful device-level assertion is not certified by the
facade. No input modem-line status properties are supplied. In particular, API 1
`DTR` is a **flow-control switch**; aliasing it to an output-state setter would be
incorrect, so it is absent. There is no extra RTS alias.

Use the facade on one owning thread and call Close explicitly. As with native
SerialConnection, applications must service their main event loop for native
reader dispatch/retention cleanup; the facade does not run an event loop inside
reads. It does not forward DataAvailable/Error/LineStateChanged or implement
Poll, Reset, Flush, SetBreak/ClearBreak, LeaveDTROnClose, XmitWait,
BytesLeftToSend, Handle, CTS/DSR/DCD/RI status, or DTR flow control. Those need
additional backend support; no flags or zero-status substitutes are stored.

## Dependency staging

New opt-in dependency: `/usr/share/buoy/packages/serialio-1.0.0.buipkg`, staged
unchanged beside RBClassic in the consuming project's temporary `packages/`.
Its archive provides native serial runtime slices for all six target platforms,
plus Windows import libraries. No new native bridge, external library install,
or installed-package/cache edit is required. The compiler extracts/stages its
matching native payload when compiling a consumer.
