---
title: "rbclassic \u00b7 RBFoundation functions"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: []
dependencies: []
symbols: ["Abs", "Acos", "Asin", "Atan", "Atan2", "Bin", "CDbl", "CStr", "CallLater", "CancelCallLater", "Ceiling", "Chr", "CoreCount", "Cos", "DebugLog", "DecodeBase64", "DecodeHex", "DecodeURLComponent", "DoEvents", "EncodeBase64", "EncodeHex", "EncodeURLComponent", "Exp", "Floor", "Format", "FoundationKeyNameForMacKeyCode", "FoundationMessageBox", "GenerateJSON", "Hex", "Log", "Max", "Microseconds", "Min", "Oct", "ParseJSON", "ParseJSONTree", "Pow", "Quit", "Rnd", "Round", "Sign", "Sin", "SleepCurrent", "Sqrt", "StartMethod", "Str", "Tan", "Val", "WindowCount", "XojoKeyNameForMacKeyCode", "XojoMessageBox", "YieldToNext"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · RBFoundation functions

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## RBFoundation functions

### CDbl

`Public Function CDbl(s As String) As Double`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `s` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### Chr

`Public Function Chr(value As Integer) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### Hex

`Public Function Hex(n As Integer) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### Oct

`Public Function Oct(n As Integer) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### Bin

`Public Function Bin(n As Integer) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### Abs

`Public Function Abs(value As Double) As Double`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `Double` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### Abs (overload 2)

`Public Function Abs(value As Integer) As Integer`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### Round

`Public Function Round(value As Double) As Double`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `Double` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### Ceiling

`Public Function Ceiling(value As Double) As Double`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `Double` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### Floor

`Public Function Floor(value As Double) As Double`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `Double` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### Sqrt

`Public Function Sqrt(value As Double) As Double`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `Double` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### Pow

`Public Function Pow(baseValue As Double, exponent As Double) As Double`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `baseValue` | `Double` | `ByVal` | Required |
| `exponent` | `Double` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### Exp

`Public Function Exp(value As Double) As Double`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `Double` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### Log

`Public Function Log(value As Double) As Double`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `Double` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### Sin

`Public Function Sin(value As Double) As Double`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `Double` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### Cos

`Public Function Cos(value As Double) As Double`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `Double` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### Tan

`Public Function Tan(value As Double) As Double`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `Double` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### Asin

`Public Function Asin(value As Double) As Double`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `Double` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### Acos

`Public Function Acos(value As Double) As Double`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `Double` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### Atan

`Public Function Atan(value As Double) As Double`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `Double` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### Atan2

`Public Function Atan2(y As Double, x As Double) As Double`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `y` | `Double` | `ByVal` | Required |
| `x` | `Double` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### Sign

`Public Function Sign(value As Double) As Integer`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `Double` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### Min

`Public Function Min(v1 As Double, v2 As Double, ParamArray rest As Double) As Double`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `v1` | `Double` | `ByVal` | Required |
| `v2` | `Double` | `ByVal` | Required |
| `rest` | `Double` | `ParamArray` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### Max

`Public Function Max(v1 As Double, v2 As Double, ParamArray rest As Double) As Double`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `v1` | `Double` | `ByVal` | Required |
| `v2` | `Double` | `ByVal` | Required |
| `rest` | `Double` | `ParamArray` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### Rnd

`Public Function Rnd() As Double`

No parameters.

#### Returns

| Type |
| --- |
| `Double` |

### Microseconds

`Public Function Microseconds() As Integer`

No parameters.

#### Returns

| Type |
| --- |
| `Integer` |

### CoreCount

`Public Function CoreCount() As Integer`

No parameters.

#### Returns

| Type |
| --- |
| `Integer` |

### DebugLog

`Public Sub DebugLog(msg As String)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `msg` | `String` | `ByVal` | Required |

Returns: no value.

### Str

`Public Function Str(v As Integer) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `v` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### Str (overload 2)

`Public Function Str(v As Double) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `v` | `Double` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### Str (overload 3)

`Public Function Str(v As Boolean) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `v` | `Boolean` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### Str (overload 4)

`Public Function Str(v As Double, formatSpec As String) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `v` | `Double` | `ByVal` | Required |
| `formatSpec` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### CStr

`Public Function CStr(v As Integer) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `v` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### CStr (overload 2)

`Public Function CStr(v As Double) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `v` | `Double` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### CStr (overload 3)

`Public Function CStr(v As Boolean) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `v` | `Boolean` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### Format

`Public Function Format(n As Double, formatSpec As String) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `n` | `Double` | `ByVal` | Required |
| `formatSpec` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### EncodeHex

`Public Function EncodeHex(s As String, insertSpaces As Boolean = False) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `s` | `String` | `ByVal` | Required |
| `insertSpaces` | `Boolean` | `ByVal` | `False` |

#### Returns

| Type |
| --- |
| `String` |

### EncodeHex (overload 2)

`Public Function EncodeHex(data As MemoryBlock, insertSpaces As Boolean = False) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `data` | `MemoryBlock` | `ByVal` | Required |
| `insertSpaces` | `Boolean` | `ByVal` | `False` |

#### Returns

| Type |
| --- |
| `String` |

### EncodeBase64

`Public Function EncodeBase64(data As MemoryBlock, lineWrap As Integer = 0) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `data` | `MemoryBlock` | `ByVal` | Required |
| `lineWrap` | `Integer` | `ByVal` | `0` |

#### Returns

| Type |
| --- |
| `String` |

### DecodeHex

`Public Function DecodeHex(s As String) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `s` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### EncodeBase64 (overload 2)

`Public Function EncodeBase64(s As String, lineWrap As Integer = 0) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `s` | `String` | `ByVal` | Required |
| `lineWrap` | `Integer` | `ByVal` | `0` |

#### Returns

| Type |
| --- |
| `String` |

### DecodeBase64

`Public Function DecodeBase64(s As String) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `s` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### EncodeURLComponent

`Public Function EncodeURLComponent(s As String) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `s` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### DecodeURLComponent

`Public Function DecodeURLComponent(s As String, encoding As Text.Encodings = Text.Encodings.UTF8) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `s` | `String` | `ByVal` | Required |
| `encoding` | `Text.Encodings` | `ByVal` | `Text.Encodings.UTF8` |

#### Returns

| Type |
| --- |
| `String` |

### ParseJSON

`Public Function ParseJSON(value As String) As JSONItem`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `JSONItem` |

### GenerateJSON

`Public Function GenerateJSON(value As JSONItem, expanded As Boolean = False) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `JSONItem` | `ByVal` | Required |
| `expanded` | `Boolean` | `ByVal` | `False` |

#### Returns

| Type |
| --- |
| `String` |

### GenerateJSON (overload 2)

`Public Function GenerateJSON(value As JSONItem, options As JSONOptions) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `JSONItem` | `ByVal` | Required |
| `options` | `JSONOptions` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ParseJSONTree

`Public Function ParseJSONTree(value As String) As Variant`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Variant` |

### GenerateJSON (overload 3)

`Public Function GenerateJSON(value As Variant, expanded As Boolean = False) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `Variant` | `ByVal` | Required |
| `expanded` | `Boolean` | `ByVal` | `False` |

#### Returns

| Type |
| --- |
| `String` |

### GenerateJSON (overload 4)

`Public Function GenerateJSON(value As Variant, options As JSONOptions) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `value` | `Variant` | `ByVal` | Required |
| `options` | `JSONOptions` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### DoEvents

`Public Sub DoEvents(ms As Integer = 10)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `ms` | `Integer` | `ByVal` | `10` |

Returns: no value.

### XojoMessageBox

`Public Function XojoMessageBox(message As String) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `message` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### WindowCount

`Public Function WindowCount() As Integer`

No parameters.

#### Returns

| Type |
| --- |
| `Integer` |

### Quit

`Public Sub Quit(exitCode As Integer = 0)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `exitCode` | `Integer` | `ByVal` | `0` |

Returns: no value.

### SleepCurrent

`Public Sub SleepCurrent(ms As Integer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `ms` | `Integer` | `ByVal` | Required |

Returns: no value.

### YieldToNext

`Public Sub YieldToNext()`

No parameters.

Returns: no value.

### StartMethod

`Public Function StartMethod(action As XojoThreadAction) As Thread`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `action` | `XojoThreadAction` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Thread` |

### CallLater

`Public Function CallLater(delayMs As Integer, action As TimerAction) As Timer`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `delayMs` | `Integer` | `ByVal` | Required |
| `action` | `TimerAction` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Timer` |

### CancelCallLater

`Public Sub CancelCallLater(t As Timer)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `t` | `Timer` | `ByVal` | Required |

Returns: no value.

### CancelCallLater (overload 2)

`Public Sub CancelCallLater(action As TimerAction)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `action` | `TimerAction` | `ByVal` | Required |

Returns: no value.

### XojoKeyNameForMacKeyCode

`Public Function XojoKeyNameForMacKeyCode(code As Integer) As KeyName`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `code` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `KeyName` |

### Val

`Public Function Val(text As String) As Double`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `text` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Double` |

### FoundationMessageBox

`Public Function FoundationMessageBox(message As String) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `message` | `String` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### FoundationKeyNameForMacKeyCode

`Public Function FoundationKeyNameForMacKeyCode(code As Integer) As KeyName`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `code` | `Integer` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `KeyName` |
