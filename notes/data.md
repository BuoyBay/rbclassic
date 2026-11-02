# ClassicData implementation contracts

Scope: `modules/ClassicData.bui`, this note. The module imports `Xojo`; it never imports the RBClassic entry or changes bundled sources. It provides a defined subset of Variant and Date behavior.

## Integration and exports

Keep `Public Import ClassicData` in the entry. It exports `ClassicDate`, the new distinct `ClassicVariant`, and extensions. Keep `Public Import ClassicData.{ IsNumeric }` for the unqualified Variant overload alongside Xojo's String overload. Selective free-function imports can also expose `Count`, `Clear`, `IsNull`, `DoubleValue`, `IntegerValue`, `Int64Value`, `Int32Value`, `UInt32Value`, `UInt64Value`, `BooleanValue`, `ObjectValue`, and the new `SingleValue`, `CurrencyValue`, `ColorValue`, `PtrValue`. There is no entry/manifest change in this scope.

`ClassicVariant` is a separate class, not a subclass or replacement for the sealed foundation `Variant`. Source migrations opt into its type and `ClassicVariant.From(...)` factories. All foundation scalar widths have exact factory overloads so an Integer cannot accidentally select the Single overload. `FromObject` explicitly boxes arbitrary objects. There are no new implicit incoming conversion operators.

No additional native library or dependency staging is needed for ClassicData beyond the existing Xojo dependencies. Locale and DateTime operations require installed native locale data.

## Foundation Variant extensions

Existing exact signed/unsigned integer conversion, decimal/exponent grammar, dictionary Count/Clear, Boolean/object coercion, null defaults and IsNumeric behavior remain covered by all prior assertions. Numeric strings are invariant decimal text, not localized numbers. Integer conversion truncates toward zero; malformed strings and range errors throw. Sized integer boundaries, including signed minimum and UInt64 maximum, do not round through Double.

New accessors:

- `SingleValue`: numeric extraction and actual binary32 narrowing; a finite magnitude above binary32 maximum throws `OverflowException`. Stored Double NaN/infinity may narrow as nonfinite Single values. Null produces zero.
- `CurrencyValue`: native fixed-point Currency, with exact string-to-scaled-Int64 conversion and four-place rounding half away from zero. Exact maximum/minimum strings and exponents are supported. It avoids the observed native Currency.Parse maximum-boundary failure. Integers use checked Currency.FromInteger; Double uses Currency.FromDouble. Numeric range errors throw OverflowException, grammar errors TypeMismatchException. Null produces Currency.Zero.
- `ColorValue`: extracts a boxed native Color with all RGBA channels; null produces black; other kinds throw TypeMismatchException. This is object extraction, not a new foundation Color payload kind or a guessed packed-integer color conversion.
- `PtrValue`: null returns Nil; every nonnull foundation payload throws. A foundation Integer is never silently reinterpreted as a pointer.

## Distinct ClassicVariant payloads and outgoing paths

`Type()` returns legacy scalar tags (Single 4, Currency 6, Date 7, Color 16, Ptr 26), the existing scalar mapping for wrapped foundation values, or array tag 4096 OR element tag. The foundation payload Kind is untouched. `IsNull`, `IsNumeric`, and typed accessors are methods and can use the normal property-style method syntax.

Single and Currency payloads retain their actual native types. Currency integer extraction divides exact minor units by 10000 and truncates toward zero. Its string extraction uses native fixed-four-place Currency formatting. Color retains native RGBA. Ptr retains an opaque borrowed address; it is never dereferenced, owned or freed. Date boxing snapshots a copy; DateValue and the outgoing Date conversion return independent copies. The Date tag and local civil value remain distinct from foundation Double/Object kinds. Date numeric extraction uses its civil TotalSeconds; this is an explicit adapter policy.

Array factories accept `Array Of Integer`, `Array Of Double`, `Array Of String`, or heterogeneous `Array Of ClassicVariant`. Typed element tags are 3/5/8; heterogeneous arrays use element tag 0. Factories copy the outer array, including fixed-mode source arrays. `ArrayValue`, `IntegerArrayValue`, `DoubleArrayValue`, and `StringArrayValue` return new resizable outer arrays. Element conversion errors throw; nested ClassicVariant object references are not recursively cloned. This is a snapshot of array membership, not a live alias of the original typed array.

Outgoing explicit `CType` supports Integer, Double, Boolean, String, Ptr, Color, ClassicDate and foundation Variant. Currency/Single/sized-width/array extraction uses the named accessors because those outgoing operator target shapes are not all supported by the compiler. `ToVariant()` preserves existing wrapped foundation payloads; it rejects Single, Currency, Date, Color, Ptr and every array. It never changes an extended payload into a Double/Object while pretending its kind survived. UInt64 StringValue uses the existing exact UInt64 formatter.

Unsupported: Variant arithmetic/comparison, implicit outgoing numeric assignment, arbitrary array element types, multidimensional arrays, general object conversion operators, packed color/integer reinterpretation, CFString/CString/PString/WString and pointer lifetime management. Foundation Variant.StringValue is unchanged. Typed null extended values preserve their declared tag; broad cross-kind null coercion is not promised.

## ClassicDate civil calendar and comparison

Use ClassicDate for migrated legacy Date declarations. Existing constructors cover now/local, independent copy, local civil components, explicit fixed GMTOffset, and DateTime. Supported calendar years are 1601–9999. `ToDateTime()` returns the immutable native timestamp and zone.

TotalSeconds is **local civil seconds since 1904-01-01 midnight**, with the verified 2,082,844,800-second civil Unix offset. It is zero at that midnight in UTC, New York and Kolkata. It is deliberately different from absolute UTC elapsed seconds. Fractions round-trip at native millisecond precision. Component/SQL/calendar rebuilding discards milliseconds.

All six comparison operators and `Compare` compare civil TotalSeconds; `CompareInstant` compares UTC SecondsFrom1970. These policies are distinct across offsets: changing GMTOffset preserves an instant while changing its civil comparison value. This wave does not claim a native Xojo oracle settled every cross-zone comparison edge. `Is` still tests identity; equal copies compare equal. Equality with Nil follows Buoy reference rules; Compare/CompareInstant reject a Nil argument.

`Copy()` is independent. `AddCalendar(years = 0, months = 0, days = 0)` performs one atomic normalized calendar rebuild, avoiding intermediate invalid dates. It is calendar arithmetic, not elapsed-duration arithmetic: a New York spring-transition day can span 23 UTC hours. `IsLeapYear` and `DaysInMonth` apply Gregorian century/400-year rules. Existing DayOfWeek, DayOfYear, Sunday-start WeekOfYear and DST readouts remain.

Year/Month/Day/Hour/Minute/Second setters retain rollover normalization. Strict SQLDate/SQLDateTime setters reject invalid formats/calendars and leave state unchanged. SQLDate preserves hour/minute/second. Local DST gaps and folds reject; explicit fixed offsets disambiguate folds. Offset resolution validates candidate civil values using offsets sampled over surrounding days. GMTOffset must resolve to whole seconds within +/-18 hours; setting it preserves the instant. Fixed offsets do not observe DST. Huge/out-of-range dates throw rather than resetting to the legacy zero epoch.

`ShortDate`, `LongDate`, `ShortTime`, `LongTime`, and `FormatDate(dateStyle, timeStyle, locale)` use native DateTime styled formatting. `FormatDate(pattern, locale)` accepts the runtime's cross-platform custom pattern language. On Linux default date properties honor LC_ALL, then LC_TIME, then LANG without changing global locale state; codeset/modifier suffixes are removed for Locale lookup. Other platforms use Locale.Current. Invalid/uninstalled explicit preferences throw. FormatDate rejects Nil locale.

These styled properties use the available native Short/Long styles. They do not promise old Xojo's exact Windows/Mac preference-style mapping (in particular Mac LongDate's Full-style requirement), AbbreviatedDate, arbitrary preference overrides, localized date parsing, or a bundled named-zone database. No Medium style is invented where the runtime provides none. Historical rapid timezone transitions and foreign native formatting remain uncertified.

## Primary references

- [Archived Date, 2022r4](https://documentation.xojo.com/versions/2022r4/api/deprecated/date.html): 1904 local epoch, constructor/copy, normalization, calendar readouts, SQL formats, comparison operators and Date Variant value storage.
- [Archived Variant, 2023r4](https://documentation.xojo.com/versions/2023r4/api/data_types/variant.html): accessors, type tags and array metadata.
- Installed `/usr/share/buoy/docs/documentation/{currency,single,datetime,locale,arrays,conversion-operators,operator-overloading}.md` and actual `.buoy/packages/Xojo/modules` supplied the native APIs. No compiler/runtime source, disassembly, installed cache changes or external issue publication was used.
