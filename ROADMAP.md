# Remaining desktop compatibility work

This backlog separates library opportunities from changes requiring Buoy runtime
or compiler support. It is not a claim that the corresponding native behavior
has been implemented. Each module's notes give the precise current boundary.

## Wave 2 integration progress

- Serial configuration, buffered byte I/O and error reporting are implemented.
  Independent verification passed six-target checks and all 16 Linux PTY baud
  cases. Physical modem-line behavior and foreign native execution remain open.
- Reusable SQLite statements, Bytes BLOB/NUL data, native metadata and explicit
  primary-key edits passed 18 compiler checks and two Linux behavior suites.
  Independent review found no blockers; foreign execution remains pending. Arbitrary SELECT
  editing and full legacy metadata shapes remain unsupported.
- Historical REALbasic 2011 originals and four mapped ports now have provenance,
  12 compiler checks and four Linux file workflows. Original Xojo execution and
  importer execution are separate, unverified stages.
- ProcessKit ARM64 Linux and Windows payloads have retained source/hash receipts.
  Linux has QEMU evidence with a glibc 2.32+ minimum; Windows has compile/link
  evidence only. Later audit-script changes invalidated strict receipt freshness;
  the final combined build used four maintained slices without these overlays.
  The runner accepts overlays only when their receipts still validate.
- Independent file/encoding review identified two case-sensitivity defects, now
  fixed with regressions. Parent revalidation passed 24 compiler checks
  and both Linux suites; foreign native execution remains open.
- Async DNS/TCP clients and a partial classic HTTP/1.0 adapter are implemented.
  Fresh independent recheck found no remaining blockers after framing, bodyless
  response, cancellation reentry and package-registration fixes. A sealed consumer
  linked and passed offline runtime cases; foreign checks remain semantic. Windows
  transport, TLS, server sockets and foreign native acceptance remain open.
- Clipboard exports and the independent native-client test lane are integrated.
  Parent verification passed 12 compiler checks and Linux GDK interchange in
  both directions, including Unicode, HTML/RTF, binary NUL and native Clear.
  Independent Linux review found no blockers; Windows/macOS execution and the
  documented Mac UTI/failure-path advisories remain pending.
- Attributed-method projections correct duplicate scopes and restore patchability
  in two sampled DBKit Toolbar classes that already rendered at the checkpoint.
  Parent verification passed 18 compiler checks, 12 original byte roundtrips and
  18 rejection cases; independent review found no implementation blockers.
  Project scope flag 2 and editable legacy media formats remain unsupported.

The historical combined package passed 258 compiler checks and 50 Linux executions/modes;
see validation for exact scope. This does not establish native
foreign-platform or full legacy parity acceptance.

Data/formatting exports are integrated. Independent review identified an exact
Currency parsing bug under a comma C numeric locale; it is fixed with regression
coverage. Parent revalidation passed 24 compiler checks and 36 Linux executions
across two optimization levels, three locales and three timezones. Native foreign
acceptance and documented Date-ordering/style policies remain open.

Control sets are exported and their native driver is integrated. Graphics metrics,
wrapping, clips, masks, cached pixel edits and shape extensions are implemented.
Opus review found a case-only Text assignment blocker, now fixed with regressions
passing the 59-check suite, and no graphics blocker. Linux-only metrics, synchronous
repaint and documented foreign/removal/ownership limits remain open.

Linux printing's dedicated verifier independently passed 12 compiler checks and
all nine PDF/mock-IPP/native-dialog modes. Desktop and ListBox new behavior passed
Linux suites. Fresh Opus rechecks passed printing corrections except a final
infinite-pen gap, now fixed with passing regressions, and passed desktop/ListBox
key ordering. Modifier routing has three additional checks, bringing desktop
acceptance to 131 checks. Module notes retain nonblocking advisories.

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

## Evidence and import work

- Add historical REALbasic/pre-2019r2 originals with provenance, alongside the
  authored API contract fixtures. Track import, projection, compile, behavior,
  native interaction and native platform execution separately.
- Investigate remaining project scope/header/control-binding projection failures
  using their original fixtures before relaxing importer validation.
- Investigate legacy `pVew` layouts and picture/sound/text resource projections;
  retained raw bytes are separate from editable reconstruction and execution.
- Execute the compatibility suite on native macOS and Windows and retain results.
- Resolve stale upstream shim gap documentation against executable package code.

Test suites and fixtures are maintainer-local and are not part of this public repository.
