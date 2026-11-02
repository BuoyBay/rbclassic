# Explicit dynamic-value transport

The bundled Xojo Variant, the strict Variant package, and ClassicVariant are
distinct. ClassicVariant's existing implicit conversion to Xojo Variant cannot
preserve Single, Currency, Color, Ptr, date or array payloads; it throws rather
than silently coercing them. That compatibility behavior remains unchanged.

`Import rbclassic` now exposes these ClassicInterop additions:

- `value.TryToVariant() As Optional Of Variant`: Some when the existing conversion
  preserves the kind, None for unsupported kinds or a Nil receiver.
- `BoxClassicValue(value) As Variant`: explicitly box a non-Nil ClassicVariant as
  an Object reference. This preserves its extended payload and does not convert
  exact Currency to Double. Nil receiver throws InvalidArgumentException.
- `TryUnboxClassicValue(value) As Optional Of ClassicVariant`: recover the same
  ClassicVariant object, or None for a different payload or Nil input.

Boxing shares the ClassicVariant object; it is transport, not serialization or
scalar coercion. Existing ClassicVariant array/date ownership rules still apply.
Using such a box as a dictionary key gives object identity, not numeric/value
identity. For exact ordinary numeric keys, VariantKit's ExactVariantDictionary
avoids the bundled Dictionary's Double/UInt64 text-canonicalization gaps. Its
signed-zero, NaN and String-case policy is explicit; it is an opt-in adapter.

Do not mix strict `Package Variant` and Xojo Variant in one namespace or assume
one can box arbitrary Buoy structures. JSON numbers through the installed Xojo
shim remain Double-based and can lose large integer IDs; transport exact IDs as
strings when using that serializer. These helpers do not change JSON semantics.
