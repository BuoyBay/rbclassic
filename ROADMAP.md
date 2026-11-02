# Remaining desktop compatibility work

This backlog separates library opportunities from changes requiring Buoy runtime
or compiler support. It is not a claim that the corresponding native behavior
has been implemented. Each module's notes give the precise current boundary.

## Native desktop work

- Foreign ListBox bridges for activation, keys, headers, mutable columns and
  multiple selection; Linux implements the documented subset.
- Native editable/checkbox/hierarchical cells with correct event ordering.
- App lifecycle and document routing, distinguishing app quit from window close,
  close veto ordering, last-window autoquit policy and exit-code propagation.
- Text editing selection, native Edit-menu state and platform event behavior
  beyond the explicitly supported desktop adapter surface.
- Control-set foreign acceptance, additional member types, released native
  ownership and complete container reparenting/focus/menu behavior.
- Foreign printer-backed Graphics and Linux physical-printer acceptance;
  Unicode, wrapping, translucency and additional font support.
- Cooperative thread semantics and truthful scheduling controls.
- Windows asynchronous networking, TLS, server sockets and foreign native
  acceptance of the POSIX client bridge.

## Adapter follow-ons

- Serial event delivery, additional backend operations, physical line-state
  validation and foreign native execution.
- Foreign native clipboard acceptance, Mac UTI/failure-path advisories and
  empty-data publication limits.
- Full legacy schema-result shapes, arbitrary editable SELECTs, composite
  identities and foreign native database execution.
- Broader Variant payloads/outgoing conversion and verified historical Date,
  Boolean coercion and locale formatting edge cases.
- Additional historical codecs, Finder alias/Windows shortcut resolution,
  filesystem error coverage beyond Delete and foreign file behavior.
- Foreign drawing metrics/wrapping, native-context state/mask-reference
  advisories, measured geometry parity and synchronous repaint.
- Windows Event Log and verified cross-platform Xojo LogLevel constants.
- ProcessKit ARM64 native hardware acceptance and Windows runtime verification.

## Import compatibility work

- Add historical REALbasic/pre-2019r2 originals with provenance, with clear source attribution. Track import, projection, compile, behavior,
  native interaction and native platform execution separately.
- Investigate remaining project scope/header/control-binding projection failures
  before relaxing importer validation.
- Investigate legacy `pVew` layouts and picture/sound/text resource projections;
  retained raw bytes are separate from editable reconstruction and execution.
- Execute the compatibility suite on native macOS and Windows and retain results.
- Resolve stale upstream shim gap documentation against executable package code.
