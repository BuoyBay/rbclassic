# ProcessKit ARM64 payload handoff

Scope: `tools/build_classic_processkit_slices.py`,
`tests/test_classic_processkit_slices.py`, this note, and generated evidence under
`local/classic-roadmap/processkit-slices/`. ProcessKit source, link/runtime trees,
existing archives, RBClassic entry/manifest/runner and distribution remain
owned by their respective maintainers. This helper never installs payloads,
publishes packages, downloads tools, or changes an installed toolchain/cache.

The roadmap's missing ARM64 Linux/Windows payload work now has an isolated build
path and concrete payloads. Linux has emulated execution evidence; Windows has
cross-compilation and consumer link evidence. Native ARM hardware acceptance and
release integration remain separate parent work.

## Reproduce

Run from the repository root:

```sh
python3 tools/build_classic_processkit_slices.py
```

The helper accepts repeated `--target arm64-linux` / `--target arm64-windows`,
`--image EXISTING_LOCAL_IMAGE`, and `--zig /absolute/path/to/existing/zig`.
It creates a unique run directory, snapshots source before each target, builds
in private temporary directories, checks current source hashes again before
marking a receipt verified, and records command output/status in `receipt.json`.
Missing prerequisites or failed checks produce a blocked receipt and exit 1;
the other requested target is still attempted. Previous run directories are
retained as evidence, including superseded and failed development attempts.

Linux requires Docker and the already available image
`buoy:font-arm-validation`, containing GCC 14 ARM64 Linux, ARM64 libc headers,
ARM64 runtime libraries and QEMU user emulation. The verified image ID is
`sha256:9de79c212731c7d2907b0e5b0651cda0669adb20f7783625e4815aca441f58fb`.
There is no host ARM64 GCC or qemu-user executable; these are in that image.
Containers use an image ID, unique names, `--rm`, `--network none`, an isolated
temporary workspace, execution timeouts and explicit removal in `finally`.
No GUI, shared desktop or binfmt registration is involved.

Windows uses the already cached Zig 0.14.1 at
`~/.cache/buoy-compressionkit-arm/zig-x86_64-linux-0.14.1/zig`. Its ARM64 MinGW
headers, CRT and LLVM linker suffice to build the actual unchanged ProcessKit
source. The host's x86_64 MinGW compiler alone would not suffice. No proprietary
SDK was fetched, and no ARM64 MSVC SDK/compiler is claimed. Both Zig caches are
redirected into the private temporary build directory. Host Python, `cc`,
`llvm-readobj-19`, `llvm-readelf-19`, `/usr/bin/buoy` for sealing and `buoy` for
checking/linking are also used. Receipts record versions, the compiler binary
hash and the Zig executable hash.

## Current validation

Fresh validation after resuming checkpoint `6b7b8685`, using Buoy 0.72.0:

- Eight Python tests pass: snapshot completeness/change detection, stale-source
  rejection, changed/missing artifact rejection, incomplete receipt rejection,
  source-sidecar disagreement, blocked receipt rejection, ELF/PE architecture
  checks (including malformed PE headers), and Docker cleanup on exceptions.
- The existing `tests/processkit_native_test.py` passes against a fresh x86_64
  Linux build of the same snapshot. Its independent assertions cover exact
  arguments, Unicode, binary and backpressured pipes, environment inheritance
  and isolation, errors, working directory, shell fallback rejection, descriptor
  isolation, direct-child cleanup and owned-tree behavior.
- The new ARM64 C driver and its spawned ARM64 fixture run under explicit
  `qemu-aarch64`. Assertions verify binary input/output including NUL and `FF`,
  separate stderr, child-only environment override, parent environment retention,
  exit status 23, live descendant before termination, owned-tree termination,
  completion polling and idempotent repeated tree termination. A descendant
  must disappear or become a zombie (no longer executing); this does not claim
  that the driver can reap an orphaned grandchild.
- Each target gets a temporary sealed ProcessKit package and a copy of the
  existing Buoy integration test. Each copy passes JSON compiler checks on all
  six targets (`x86_64-linux`, `arm64-linux`, `x86_64-darwin`, `arm64-darwin`,
  `x86_64-windows`, `arm64-windows`), with exit 0 and `errors: []`.
- Both ARM64 consumers cross-link, with architecture verified. The Linux Buoy
  consumer also executes under QEMU with the installed ARM64 Buoy runtime copied
  into the temporary workspace. Its Python fixture is x86_64; the separate C
  driver supplies the ARM64-child execution evidence above. The Windows consumer
  is not executed.
- All 19 `bpk_*` exports declared with `API` in the snapshotted native source
  are present in both payloads. Windows import-library compatibility is exercised
  by the actual Buoy ARM64 consumer link, rather than inferred from its filename.

No `.bui` source was authored or edited in this scope. Existing sources were
copied, checked, compiled and executed as described; their original tests remain
intact. No new suspected upstream defect was encountered.

## Runtime and compatibility boundaries

The Linux payload is ELF64 AArch64, SONAME `libbuoy_processkit.so`, with only
`libc.so.6` in `DT_NEEDED`. Its versioned requirements include `GLIBC_2.17` and
`GLIBC_2.32`; **this is not a glibc 2.17 compatible payload**. It was executed
against image libc 2.41 under QEMU 10.0.13, not native ARM hardware or older
Linux distributions. Buoy applications additionally need their matching Buoy
runtime libraries. This work adds no musl support.

The Windows payload is PE ARM64 with a real import `.lib`, built using Zig's
GNU Windows target and successfully consumed by Buoy's
`aarch64-pc-windows-msvc` package layout. It imports `KERNEL32.dll` and UCRT API
sets, including `api-ms-win-crt-private-l1-1-0.dll`; the full import list is in
the receipt. Availability and behavior of those imports, DLL startup, Windows
argument quoting, pipes, environment merging and job teardown still need an
actual Windows ARM64 run before runtime compatibility can be claimed. Neither
an import-library link nor six-target semantic checks establish that acceptance.
No shared Windows/macOS GUI was used.

## Exports and staging recipe

No new RBClassic module, exported symbol or selective public import is needed.
The existing ProcessKit `PipeProcess` and `ProcessException` API is unchanged;
the consumer uses `Import processkit`. Keep the existing ProcessKit dependency
alongside RBClassic/Xojo. These payloads supply its native library, not a
replacement RBClassic API. Their paths must retain these exact target triples:

```text
runtime/aarch64-unknown-linux-gnu/libbuoy_processkit.so
runtime/aarch64-unknown-linux-gnu/libbuoy_processkit.so.source-sha256
runtime/aarch64-pc-windows-msvc/buoy_processkit.dll
runtime/aarch64-pc-windows-msvc/buoy_processkit.dll.source-sha256
link/aarch64-pc-windows-msvc/buoy_processkit.lib
```

For parent integration, use the completed target runs named below, and verify both
receipts immediately before copying. Verification rejects changed current
package sources, missing artifacts, changed artifact hashes, inconsistent source
sidecars and wrong binary architecture. A source update requires a new build;
do not rewrite old receipts to fit it.

```sh
LINUX=local/classic-roadmap/processkit-slices/46a7e93e9b1b43408cb9631f06df84c5/arm64-linux
WINDOWS=local/classic-roadmap/processkit-slices/46a7e93e9b1b43408cb9631f06df84c5/arm64-windows
python3 tools/build_classic_processkit_slices.py --verify-receipt "$LINUX/receipt.json"
python3 tools/build_classic_processkit_slices.py --verify-receipt "$WINDOWS/receipt.json"
python3 tools/build_rbclassic.py --no-publish --test \
  --processkit-slice-receipt "$LINUX/receipt.json" \
  --processkit-slice-receipt "$WINDOWS/receipt.json"
```

The final command uses the parent's receipt-aware temporary staging option;
it is the integration recipe, not an integrated-suite result claimed here.
For manual staging instead:

Prepare the parent's isolated ProcessKit staging directory from the matching
`manifest.json`, `modules/` and optional `resources/`. Keep existing target
payloads only when their source receipts match the current native source, using
the same rule as `tools/build_processkit.py`. Then overlay the two verified
`runtime/` trees and the Windows `link/` tree. For an already prepared temporary
`$STAGE` (not the shared source tree), the copy/seal steps are:

```sh
mkdir -p "$STAGE/runtime" "$STAGE/link"
cp -a "$LINUX/runtime/." "$STAGE/runtime/"
cp -a "$WINDOWS/runtime/." "$STAGE/runtime/"
cp -a "$WINDOWS/link/." "$STAGE/link/"
/usr/bin/buoy pkg seal "$STAGE" -o "$STAGE/../processkit-0.1.0.buipkg"
```

Stage that sealed package into the parent's isolated RBClassic consumer's
`packages/`, then run the parent integration suite. Do not substitute a stale
global package archive. Installation into maintained runtime/link trees, package
replacement, release manifests and roadmap acceptance remain parent actions.
Existing baseline packages and foreign runtime claims are preserved.

## Artifact receipts

The current rebuilt Linux receipt is
`local/classic-roadmap/processkit-slices/46a7e93e9b1b43408cb9631f06df84c5/arm64-linux/receipt.json`.
The current rebuilt Windows receipt is
`local/classic-roadmap/processkit-slices/46a7e93e9b1b43408cb9631f06df84c5/arm64-windows/receipt.json`.
Each target directory contains `receipt.json`, the exact source snapshot,
`harness.c`, the native payload (and Windows import library), source sidecars and
proof executables. Receipts include full SHA256 hashes and commands. This rebuild
uses the maintained native source and updated module, including the new
ProcessInspection sibling modules; all four modules are snapshotted and imported
by the checked consumers. Previous runs (including `d03bbad131b6400ca4b8262801c24349`,
`7ea98774fa52441293b6dfd88f8e8cd7` and `6ff716e419944e8289fc263b1bf1aaad`) are
stale and remain unchanged as evidence. All eight helper tests, twelve compiler
checks and the native/emulated behavior tests described above passed again.
ProcessInspection APIs were imported and checked; this scope does not claim
runtime coverage for those newly maintained APIs. No shared ProcessKit files or
maintained runtime slices were edited during this rebuild.

Shared native source SHA256:
`b407903fab76dfc5c9929b6e68230fc4e8f43765845f7bc2490d1bdc98d192d2`.
Manifest SHA256:
`76964e3438f686a1df1c846b05bfb8fc96790f28574d9d85341db2f60a15b949`.
Module SHA256:
`938b11dd4ed678ec967b856a637e2841c11944071940fc9bb9675250e9dc04f9`.

Linux shared library SHA256:
`da3e591a498e4b871f49d44565b5fb07aa7d922203328075e9da0e53994fb29d`.
Windows DLL SHA256:
`6badff0a51934671b19784dacc701a26ae60c67fbd5fbabaf149ea9113fa0bc2`.
Windows import library SHA256:
`53486d02ebfde2ab05adedc600a0f0c0d706bc7aac2fe49b7164cfe3028523fa`.

The latest rebuild above refreshes `tools/build_processkit.py` to SHA256
`56b39f274f34f36506127fe9ab9170245d4bed0a9241d6385bf6c79ade740b10`.
Both receipts passed immediate current-source verification. Earlier `e8f949`
evidence still matches the native source and binaries, but is ineligible under
the unchanged all-recorded-source freshness policy because that build helper
changed. Prior receipts were preserved verbatim. This was one new build attempt;
all eight helper tests and the twelve compiler checks passed, as did native Linux
regressions and Linux ARM64 emulated execution. Runtime boundaries remain unchanged.

Test suites and fixtures are maintainer-local and are not part of this public repository.
