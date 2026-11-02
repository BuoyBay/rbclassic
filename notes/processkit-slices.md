# ProcessKit target requirements

RBClassic process operations use the ProcessKit native library. A consumer must
include a runtime slice and, on Windows, its matching import library for the
selected target. Build them from the maintained ProcessKit source before sealing
when targeting an additional architecture.

The ARM64 Linux payload requires glibc 2.32 or newer, plus the matching Buoy
runtime libraries. It is not a musl build. Emulated execution does not establish
behavior on physical ARM hardware or on older Linux distributions.

The Windows ARM64 payload uses the PE ARM64 format and a matching import `.lib`.
Cross-compilation and linking do not establish native Windows ARM64 behavior.

See [ProcessKit](https://github.com/BuoyBay/processkit) for native build commands,
ABI requirements and the current target coverage.
