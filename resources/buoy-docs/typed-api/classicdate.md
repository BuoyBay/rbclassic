---
title: "rbclassic \u00b7 ClassicDate"
summary: "Source-derived public signatures, properties, parameters, defaults, and return values."
category: "Reference"
order: 21
types: ["ClassicDate"]
dependencies: []
symbols: ["ClassicDate"]
related: ["../api.md", "../getting-started.md", "../index.md"]
---

# rbclassic · ClassicDate

Generated from the package source declarations. Platform guards are shown where present; inherited members are documented on the base type. See the [API contracts](../api.md) for behavior and limitations.

## ClassicDate

`Public Class ClassicDate`

### Properties

| Name | Type | Read-Only | Shared | Default | Description |
| --- | --- | --- | --- | --- | --- |
| `DaysInMonth` | `Integer` | Yes | No | — | — |
| `IsLeapYear` | `Boolean` | Yes | No | — | — |
| `ShortDate` | `String` | Yes | No | — | — |
| `LongDate` | `String` | Yes | No | — | — |
| `ShortTime` | `String` | Yes | No | — | — |
| `LongTime` | `String` | Yes | No | — | — |
| `Year` | `Integer` | No | No | — | — |
| `Month` | `Integer` | No | No | — | — |
| `Day` | `Integer` | No | No | — | — |
| `Hour` | `Integer` | No | No | — | — |
| `Minute` | `Integer` | No | No | — | — |
| `Second` | `Integer` | No | No | — | — |
| `DayOfWeek` | `Integer` | Yes | No | — | — |
| `DayOfYear` | `Integer` | Yes | No | — | — |
| `WeekOfYear` | `Integer` | Yes | No | — | — |
| `IsDaylightSavingsTime` | `Boolean` | Yes | No | — | — |
| `GMTOffset` | `Double` | No | No | — | — |
| `TotalSeconds` | `Double` | No | No | — | — |
| `SQLDate` | `String` | No | No | — | — |
| `SQLDateTime` | `String` | No | No | — | — |

### Constructor

`Public Sub Constructor()`

No parameters.

Returns: no value.

### Constructor (overload 2)

`Public Sub Constructor(copyDate As ClassicDate)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `copyDate` | `ClassicDate` | `ByVal` | Required |

Returns: no value.

### Constructor (overload 3)

`Public Sub Constructor(year As Integer, month As Integer = 1, day As Integer = 1, hour As Integer = 0, minute As Integer = 0, second As Integer = 0)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `year` | `Integer` | `ByVal` | Required |
| `month` | `Integer` | `ByVal` | `1` |
| `day` | `Integer` | `ByVal` | `1` |
| `hour` | `Integer` | `ByVal` | `0` |
| `minute` | `Integer` | `ByVal` | `0` |
| `second` | `Integer` | `ByVal` | `0` |

Returns: no value.

### Constructor (overload 4)

`Public Sub Constructor(year As Integer, month As Integer, day As Integer, hour As Integer, minute As Integer, second As Integer, gmtOffset As Double)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `year` | `Integer` | `ByVal` | Required |
| `month` | `Integer` | `ByVal` | Required |
| `day` | `Integer` | `ByVal` | Required |
| `hour` | `Integer` | `ByVal` | Required |
| `minute` | `Integer` | `ByVal` | Required |
| `second` | `Integer` | `ByVal` | Required |
| `gmtOffset` | `Double` | `ByVal` | Required |

Returns: no value.

### Constructor (overload 5)

`Public Sub Constructor(source As DateTime)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `source` | `DateTime` | `ByVal` | Required |

Returns: no value.

### Compare

`Public Function Compare(other As ClassicDate) As Integer`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `other` | `ClassicDate` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### CompareInstant

`Public Function CompareInstant(other As ClassicDate) As Integer`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `other` | `ClassicDate` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Integer` |

### =

`Public Operator =(other As ClassicDate) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `other` | `ClassicDate` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### <>

`Public Operator <>(other As ClassicDate) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `other` | `ClassicDate` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### <

`Public Operator <(other As ClassicDate) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `other` | `ClassicDate` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### <=

`Public Operator <=(other As ClassicDate) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `other` | `ClassicDate` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### >

`Public Operator >(other As ClassicDate) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `other` | `ClassicDate` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### >=

`Public Operator >=(other As ClassicDate) As Boolean`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `other` | `ClassicDate` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `Boolean` |

### Copy

`Public Function Copy() As ClassicDate`

No parameters.

#### Returns

| Type |
| --- |
| `ClassicDate` |

### AddCalendar

`Public Sub AddCalendar(years As Integer = 0, months As Integer = 0, days As Integer = 0)`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `years` | `Integer` | `ByVal` | `0` |
| `months` | `Integer` | `ByVal` | `0` |
| `days` | `Integer` | `ByVal` | `0` |

Returns: no value.

### FormatDate

`Public Function FormatDate(dateStyle As DateTime.Formats, timeStyle As DateTime.Formats, loc As Locale) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `dateStyle` | `DateTime.Formats` | `ByVal` | Required |
| `timeStyle` | `DateTime.Formats` | `ByVal` | Required |
| `loc` | `Locale` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### FormatDate (overload 2)

`Public Function FormatDate(pattern As String, loc As Locale) As String`

#### Parameters

| Name | Type | Passing | Default |
| --- | --- | --- | --- |
| `pattern` | `String` | `ByVal` | Required |
| `loc` | `Locale` | `ByVal` | Required |

#### Returns

| Type |
| --- |
| `String` |

### ToDateTime

`Public Function ToDateTime() As DateTime`

No parameters.

#### Returns

| Type |
| --- |
| `DateTime` |
