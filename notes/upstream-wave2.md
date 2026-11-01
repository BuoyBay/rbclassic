# Wave 2 upstream handoff

These twelve local candidates have independent reproduction or challenge evidence.
They remain unpublished and outside the central numbered queue. Reproduction is
not a claim that every observation violates a documented contract. Check upstream
duplicates and reconcile scope before preparing reports. No installed toolchain
or extracted package was patched.

| Candidate | Independent outcome | Disposition and local boundary |
| --- | --- | --- |
| DATA-001 | Scientific masks add a sign and produce incorrect fractional precision. | Retain both observed symptoms; a shared root cause is unproven. ClassicFormatMask avoids the foundation mask path. |
| DATA-002 | Currency.Parse rejects the exact maximum; minimum parsing and maximum minor-unit construction succeed. | Exact ClassicData decimal accumulation avoids the rejected boundary. |
| DATA-003 | Fresh German preferences yield a dot from Locale.Current but a comma from an explicit locale; setlocale does not fix the control. | Linux adapter defaults resolve preference identifiers explicitly. Foreign behavior is unverified. |
| CFE-001 | Ordinary remove/utimensat declarations pass semantics but fail Linux linking; installed libc stubs omit exports. | SDK export-coverage triage. Complete libc coverage is not promised; reconcile with existing export-gap records. Optional bindings are the local workaround. |
| CFE-002 | Ordinary realpath with Nil output fails; optional lookup and a caller-allocated output buffer succeed. | Native symbol-version controls reproduce old glibc compatibility behavior. Symbol selection is strongly supported; compiler-internal causation is unproven. |
| CC-001 | First remote TextAvailable is False; reading Text then querying yields True. | Initial asynchronous discovery, not a demonstrated steady-state freshness defect. The wrapper primes the live text read. |
| CC-002 | Empty custom publication is omitted; an independent GDK owner can serve empty bytes. | Publication limitation reproduced; the documented empty-payload guarantee remains unclear. Windows/Linux adapter writes reject empty raw data. |
| CS-001 | Missing removal methods reject at compile time; moving a manually detached control produces a GTK critical. | Existing removal-primitive enhancement, not a new runtime defect. AddSubview after reparenting updates placement; only clearing placement is missing. |
| CW2-PRINT-001 | FillPath/StrokePath change colour/width inside an open PDF path, fail with 4177, and leave subsequent drawing on that page broken. | Package-source and native controls support the path-state cause. Other pages and ToBytes still work. Adapter checks/state setup precede its direct fill path. |
| CWD-001 | A plain Button event caught across ShowModally segfaults; uncaught controls reach UnhandledException and abort. | Broader runtime event-dispatch boundary than PerformClick alone. Timer was caught without crashing in the author's control; review-reported hangs were not reproduced there. Handle errors inside handlers. |
| CWD-002 | Three documented window members are missing on every semantic target, producing four diagnostics including a follow-on assignment error. | Documentation/compiler surface mismatch; no guessed replacement API is supplied. |
| LISTBOX-001 | An interface-typed reference cannot target Object through CType/TryCast/IsA, while concrete/base-class targets work. | Object-target RTTI/conversion candidate. The bridge stores a weak Object reference directly and casts to its client interface. |

Repros, original author evidence, references and workaround-removal rules remain
in the scoped directories:

- Data/formatting
- Native files
- Clipboard
- Control sets
- Printing
- Desktop
- ListBox

Review probes also exercised cleanup, lifetime and negative controls. Temporary
review workspaces are supporting evidence, not durable release receipts. The
module notes distinguish foreign semantic checks, cross-linking, emulation and
native execution. No native Windows/macOS or physical-printer acceptance follows
from these Linux reproductions.

Test suites and fixtures are maintainer-local and are not part of this public repository.
