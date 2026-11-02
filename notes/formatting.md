# ClassicFormatting contracts

## Integration

The entry module uses `Public Import ClassicFormatting` and selectively re-export `ClassicCStr` and `ClassicFormatMask`. These are intentionally unique names. ClassicCore overloads can route to
ClassicFormatMask when legacy Format semantics are required, including its
default treatment of negative numbers.

No new package or native helper is required. Production code declares only C-variadic `sprintf`: `Lib "c"` on Linux/macOS, `Lib "msvcrt"` on Windows. Buffers are Bytes, precision is limited to 18 decimal places, and finite binary64 rendering has ample room in a 768-byte buffer. There is no dynamic locale handle, process-wide setlocale call, native cache change, custom dylib/DLL, or generated runtime payload to stage. Native runtime locale data must actually exist for requested identifiers.

The formatter recovers decimal/fraction fields from printf's ASCII digits and known fraction width, then inserts the requested Locale separator. This works when the caller's C locale has a comma separator and leaves that C locale selected. It does not rely on printf starting in C locale.

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

Rounding for floating inputs uses native libc under the process's floating-point
rounding mode. The Linux default is ties-to-even. Exact integer scientific
rounding is explicitly ties-to-even. Check native rounding behavior on each host;
compiler checks and cross-linking do not establish it.

Masks over 1024 scalars, more than three sections, trailing escapes, unescaped unknown literals, split numeric fields, missing digit placeholders, misplaced exponent markers/signs, repeated percent tokens, and excessive precision/padding throw InvalidArgumentException. Percent overflow to infinity also throws. Uppercase/lowercase exponent markers are supported; `E+00`/`E-00` exponent-padding syntax, quoted literals, scaling commas, arbitrary grouping patterns (including Indian 3/2 grouping), embedded signs, fill/alignment tokens, and full modern spreadsheet masks are outside this subset. A grouping comma is a grouping request, not a scale operation. The current mask function is not advertised as a complete Xojo Format replacement.

## Primary references

The adapter follows these archived API contracts:

- [CStr, 2022r4](https://documentation.xojo.com/versions/2022r4/api/text/cstr.html): locale decimal conversion and seven significant digits.
- [Format, 2022r4](https://documentation.xojo.com/versions/2022r4/api/text/format.html): magnitude/sign behavior, sections, escapes, percent, scientific notation and examples.
- [Date, 2022r4](https://documentation.xojo.com/versions/2022r4/api/deprecated/date.html) and [Variant, 2023r4](https://documentation.xojo.com/versions/2023r4/api/data_types/variant.html) for the companion data contracts.
