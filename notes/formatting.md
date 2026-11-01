# ClassicFormatting contracts and verification

Scope: `modules/ClassicFormatting.bui`, `tests/classic_formatting_test.bui`, and this note. The module imports Xojo and ClassicData, never the RBClassic entry. It expands the locale/formatting roadmap item without changing ClassicCore or the invariant foundation CStr/Format functions.

## Parent integration

The parent can add `Public Import ClassicFormatting` and selectively re-export `ClassicCStr` and `ClassicFormatMask`. These are intentionally unique names. ClassicCore's existing ClassicFormat overloads can be routed to ClassicFormatMask by their owner if the legacy mask behavior is desired. Existing ClassicFormat tests may need to distinguish the previous foundation-mask contract from legacy Format (especially the default treatment of negative numbers).

No new package or native helper is required. Production code declares only C-variadic `sprintf`: `Lib "c"` on Linux/macOS, `Lib "msvcrt"` on Windows. Buffers are Bytes, precision is limited to 18 decimal places, and finite binary64 rendering has ample room in a 768-byte buffer. There is no dynamic locale handle, process-wide setlocale call, native cache change, custom dylib/DLL, or generated runtime payload to stage. Native runtime locale data must actually exist for requested identifiers.

The formatter recovers decimal/fraction fields from printf's ASCII digits and known fraction width, then inserts the requested Locale separator. This works when the caller's C locale has a comma separator and leaves that C locale selected. It does not rely on printf starting in C locale. The behavior test explicitly selects German LC_NUMERIC in its own process, asserts output in US/German locales, checks that the native setting survived, and restores it even when an assertion throws. TestSetLocale uses Optional Declare on Linux to avoid the shipped libc stub's missing link symbol; it is test-only.

## ClassicCStr

Overloads cover Double/Single (explicit or current locale), Integer/UInt64 (exact, with optional explicit locale), Boolean, String, ClassicDate, and foundation Variant. Booleans produce True/False; Date produces its SQLDateTime. Variant dispatch preserves exact integer widths and UInt64 text, handles null as empty text, and rejects arbitrary object conversion. Color/Currency/Ptr and general object-conversion formatting are not supplied by this numeric formatter.

Real numbers have **seven significant digits**, including normal/subnormal extremes and carry into a new exponent. The output has no thousands grouping. Fractional trailing zeros are removed. The decimal separator follows the requested locale. The explicit adapter notation policy follows general-format thresholds: scientific notation below exponent -4 or from exponent 7 upward, based on the rounded value; lowercase e, explicit exponent sign, no redundant exponent zeros. Negative zero becomes `0`. NaN and infinities throw InvalidArgumentException. Those notation/nonfinite/negative-zero policies are executable adapter choices, not an assertion that an unavailable Xojo runtime established every edge.

Linux defaults honor LC_ALL, then LC_NUMERIC, then LANG, removing codeset/modifier suffixes for native Locale lookup. This compensates for the observed Locale.Current fresh-process C snapshot. No preference variables means Locale.Current fallback. Other platforms use Locale.Current. Invalid/uninstalled preferences throw; explicit Locale arguments bypass preference resolution. Exact integer conversions never pass through Double.

## ClassicFormatMask

Double, Integer and UInt64 overloads accept an explicit Locale or use the same default-locale policy. Supported legacy grammar:

- Required `0` and optional `#` digits; fractional precision 0–18; leading-zero padding; decimal point; grouping markers with groups of three.
- `%` scales by 100; Integer/UInt64 scaling uses decimal digits and cannot overflow native integer arithmetic.
- Leading `+` or `-` controls sign output. **Without either token, magnitude is printed**, including negative inputs. This matches the archived Format contract and differs from many modern mask engines.
- One, two or three semicolon-separated sections select positive/default, negative, zero. Negative zero selects the zero/default section. Empty/literal-only sections work. Backslash escapes include literal semicolons.
- Parentheses and escaped prefix/suffix literals; one contiguous numeric field.
- Terminal `e`/`E` scientific masks, preserving the marker's case, with explicit exponent sign and unpadded exponent. Integer scientific rounding operates on exact decimal digits, including 19-digit signed values and 20-digit unsigned values.

Rounding for floating inputs uses native libc under the process's floating-point rounding mode; the Linux matrix verifies the default ties-to-even behavior, precision carries, and independently generated Python binary64 expected values. Exact integer scientific rounding is explicitly ties-to-even. Native foreign rounding behavior is pending the parent's runs; semantic checking and Windows cross-linking alone do not establish it.

Masks over 1024 scalars, more than three sections, trailing escapes, unescaped unknown literals, split numeric fields, missing digit placeholders, misplaced exponent markers/signs, repeated percent tokens, and excessive precision/padding throw InvalidArgumentException. Percent overflow to infinity also throws. Uppercase/lowercase exponent markers are supported; `E+00`/`E-00` exponent-padding syntax, quoted literals, scaling commas, arbitrary grouping patterns (including Indian 3/2 grouping), embedded signs, fill/alignment tokens, and full modern spreadsheet masks are outside this subset. A grouping comma is a grouping request, not a scale operation. The current mask function is not advertised as a complete Xojo Format replacement.

## Independent review and fixes

Independent review repeated 42 compiler checks, the 36-run locale/timezone/build
matrix and four Windows cross-links, and checked 250 additional formatting values
against Python/Decimal controls. It identified a locale-sensitive Currency
validation path in ClassicData and permissive repeated sign tokens here. Exact
Currency/integer text now uses decimal grammar validation without Double.Parse;
repeated or mixed mask signs are rejected. Added regressions exercise Currency
fraction/minimum/maximum under a comma C numeric locale and preserve that locale.
Parent validation after these fixes passed 24 six-target checks and all 36 Linux
matrix executions. Original author evidence hashes predate these fixes.

The three scoped upstream candidates independently reproduced. Locale.Current
still returned a dot separator after a successful German setlocale control, so
initialization alone is not a demonstrated fix. Scientific-mask sign/precision
symptoms need not share one root cause. Currency maximum text parsing fails while
minor-unit construction succeeds and minimum parsing succeeds. No central issue
promotion or publication is implied by these observations.

## References and final validation

Primary old references read for this wave:

- [CStr, 2022r4](https://documentation.xojo.com/versions/2022r4/api/text/cstr.html): locale decimal conversion and seven significant digits.
- [Format, 2022r4](https://documentation.xojo.com/versions/2022r4/api/text/format.html): magnitude/sign behavior, sections, escapes, percent, scientific notation and examples.
- [Date, 2022r4](https://documentation.xojo.com/versions/2022r4/api/deprecated/date.html) and [Variant, 2023r4](https://documentation.xojo.com/versions/2023r4/api/data_types/variant.html) for the companion data contracts.

Final validation after the checkpoint release, using fresh copied dependencies in `/tmp/classic-wave2-data-final-9zrw7ezb`:

- Four module/test sources each passed compiler JSON checking for x86_64-linux, arm64-linux, x86_64-darwin, arm64-darwin, x86_64-windows and arm64-windows: 24 clean checks. Three candidate repros also passed all six: 18 more checks. Each errors array was inspected. Only the known XojoDesktop.Show shadowing warning appears for Xojo imports.
- Both actual suites built at O0 and O2. Each binary ran under all combinations of UTC/America-New_York/Asia-Kolkata (actual TZ identifiers below) and en_US/de_DE/fr_FR UTF-8: **36 suite executions passed**. Existing date/integer assertions are retained. Data additions cover exact Currency bounds/rounding/overflow, real Single narrowing, payload tags, outgoing conversions, array copies, Date snapshots, comparison/copy/calendar/DST atomicity and locale formatting.
- Formatting assertions include all archived examples, exact signed/unsigned extreme masks, grouping, optional fractions, section/escape/sign rules, negative zero, NaN/infinity rejection, binary64 extremes and unsupported masks. The committed precision corpus contains 87 seven-digit cases in US and German locales and 35 fixed-mask cases independently generated with Python `format` using `random.Random(1904)`, alongside hand-selected boundaries.
- Both suites cross-linked successfully for x86_64-windows and arm64-windows. No Windows/macOS native execution or GUI action was performed. A diagnostic macOS cross-link attempt hit missing SDK frameworks/libc++ on this Linux installation; this is not a native macOS test result. The final six-target semantic checks passed.
- The parent RBClassic entry passed a fresh host compiler JSON check after the numeric CType fix. Parent integration/resealing remains outside this ownership.

Full commands, parsed diagnostics, source hashes, build logs and native output are preserved in `upstream-issues/classic-wave2-data/verification.json`. Native repro outputs have separate per-candidate evidence. Candidates are unpublished and pending independent reproduction/challenge; central queue reconciliation belongs to the parent. No Xojo runtime oracle was available. The candidate list records the scientific mask precision issue, Currency.Parse boundary rejection and Locale.Current preference issue; all have local workarounds in this wave.

Reproduce the suite in a private directory containing copies of ClassicData.bui, ClassicFormatting.bui, both tests, and `.buoy/packages` (copy existing packages, do not symlink mutable caches). Create native locale fixtures without system installation:

```sh
mkdir -p "$private_dir/locales"
localedef --no-archive -i en_US -f UTF-8 "$private_dir/locales/en_US.UTF-8"
localedef --no-archive -i de_DE -f UTF-8 "$private_dir/locales/de_DE.UTF-8"
localedef --no-archive -i fr_FR -f UTF-8 "$private_dir/locales/fr_FR.UTF-8"
```

From that directory, run `buoy classic_data_test.bui --check --diagnostic-format json` and the formatting test equivalent; repeat with every target above. Build each with `-O0` and `-O2`, then run with `LOCPATH="$private_dir/locales"`, `TZ=UTC` / `TZ=America/New_York` / `TZ=Asia/Kolkata`, and `LC_ALL=en_US.UTF-8` / `de_DE.UTF-8` / `fr_FR.UTF-8`. Every process must exit zero and print its suite PASS marker; a prior executable must not run after a failed build.
