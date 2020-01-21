[Variables]
IconNames="clear-day":"clear_day", "clear-night":"clear_night", "rain":"rain", "snow":"snow", "sleet":"sleet", "wind":"wind", "fog":"fog", "cloudy":"cloudy", "partly-cloudy-day":"partly_cloudy_day", "partly-cloudy-night":"partly_cloudy_night", "hail":"sleet", "thunderstorm":"storm", "tornado":"storm", "":"unknown"
@include=#@#Variables.inc
CurrentRegExp=.*,"summary":"(.*)","icon":"(.*)",.*,"temperature":(.*),.*
DayNRegExp="time":(.*),"summary":"(.*)","icon":"(.*)",.*,"temperatureHigh":(.*),.*,"temperatureLow":(.*),.*

TimestampOffset=11644473600
;11644473600 is the amount of seconds between 01-01-1601 and 01-01-1970. It's the difference between Unix time and Windows time.

;================================================

[MeasureLocation]
Measure=WebParser

URL=https://nominatim.openstreetmap.org/search/#WeatherLocation#?format=json&limit=1
RegExp=(?siU)"lat":"(.*)","lon":"(.*)","display_name":"(.*)"
UpdateRate=-1
StringIndex=3

FinishAction=[!Log "Location: [MeasureLocation]"] [!EnableMeasure MeasureDarkSky] [!UpdateMeasure MeasureDarkSky]

DynamicVariables=1

[MeasureLocationLatitude]
Measure=WebParser
URL=[MeasureLocation]
StringIndex=1

[MeasureLocationLongitude]
Measure=WebParser
URL=[MeasureLocation]
StringIndex=2

[MeasureLocation2]
Measure=WebParser

URL=https://nominatim.openstreetmap.org/search/#WeatherLocation#?format=json&limit=1&accept-language=#Language#
RegExp=(?siU)"display_name":"(.*)"
UpdateRate=600
StringIndex=1
DynamicVariables=1
RegExpSubstitute=1 
Substitute="(^[^,]+,).+,([^,]+)$":"\1\2"

[Unitset]
Measure=String
String=#WeatherUnits#
RegExpSubstitute=1 
DynamicVariables=1
Substitute="c":"si","f":"us","C":"si","F":"us"

;================================================

[MeasureDarkSky]
Measure=WebParser

URL=https://api.darksky.net/forecast/#Key#/[&MeasureLocationLatitude],[&MeasureLocationLongitude]?exclude=minutely,hourly,alerts,flags&units=[&Unitset]&lang=#Language#
RegExp=(?siU){.*"currently":{(.*)},"daily":{"summary":"(.*)",.*,"data":\[{(.*)},{(.*)},{(.*)},{(.*)},{(.*)},{(.*)},{(.*)},{(.*)}\]},"offset":(.*)}
UpdateRate=(60*15)

FinishAction=[!Log "Download finished." Notice] [!EnableMeasureGroup Processing] [!UpdateMeasureGroup Processing] [!UpdateMeter *] [!UpdateMeter *] [!Redraw]

Disabled=1
DynamicVariables=1

[MeasureForecastSummary]
Measure=WebParser
URL=[MeasureDarkSky]
StringIndex=2

Substitute="":"N/A"

[MeasureUTCOffset]
Measure=WebParser
URL=[MeasureDarkSky]
StringIndex=11

Substitute="":"0"

;================================================

[MeasureCurrentSummary]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#CurrentRegExp#
StringIndex=1
StringIndex2=1

Substitute="":"N/A"

[MeasureCurrentIcon]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#CurrentRegExp#
StringIndex=1
StringIndex2=2

Substitute="#IconNames#"

[MeasureCurrentTemperatureRAW]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#CurrentRegExp#
StringIndex=1
StringIndex2=3

Substitute="":"0"

[MeasureCurrentTemperature]
Group=Processing
Measure=Calc
Formula=Round([#CurrentSection#RAW])

UpdateDivider=-1
DynamicVariables=1
Disabled=1

RegExpSubstitute=1 
Substitute="-0":"0"

;================================================

[MeasureDay0Timestamp]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=3
StringIndex2=1

Substitute="":"0"

[MeasureDay0Weekday]
Group=Processing
Measure=Time

Timestamp=([MeasureDay0Timestamp]+#TimestampOffset#+[MeasureUTCOffset]*60*60)
Format=%A
FormatLocale=#Language#

UpdateDivider=-1
DynamicVariables=1
Disabled=1

[MeasureDay0WeekdayShort]
Group=Processing
Measure=Time

Timestamp=([MeasureDay0Timestamp]+#TimestampOffset#+[MeasureUTCOffset]*60*60)
Format=%a
FormatLocale=#Language#

UpdateDivider=-1
DynamicVariables=1
Disabled=1

[MeasureDay0Summary]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=3
StringIndex2=2

Substitute="":"N/A"

[MeasureDay0Icon]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=3
StringIndex2=3

Substitute="#IconNames#"

[MeasureDay0TemperatureHighRAW]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=3
StringIndex2=4

Substitute="":"0"

[MeasureDay0TemperatureHigh]
Group=Processing
Measure=Calc
Formula=Round([#CurrentSection#RAW])

UpdateDivider=-1
DynamicVariables=1
Disabled=1

RegExpSubstitute=1 
Substitute="-0":"0"

[MeasureDay0TemperatureLowRAW]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=3
StringIndex2=5

Substitute="":"0"

[MeasureDay0TemperatureLow]
Group=Processing
Measure=Calc
Formula=Round([#CurrentSection#RAW])

UpdateDivider=-1
DynamicVariables=1
Disabled=1

RegExpSubstitute=1 
Substitute="-0":"0"

;================================================

[MeasureDay1Timestamp]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=4
StringIndex2=1

Substitute="":"0"

[MeasureDay1Weekday]
Group=Processing
Measure=Time

Timestamp=([MeasureDay1Timestamp]+#TimestampOffset#+[MeasureUTCOffset]*60*60)
Format=%A
FormatLocale=#Language#

UpdateDivider=-1
DynamicVariables=1
Disabled=1

[MeasureDay1WeekdayShort]
Group=Processing
Measure=Time

Timestamp=([MeasureDay1Timestamp]+#TimestampOffset#+[MeasureUTCOffset]*60*60)
Format=%a
FormatLocale=#Language#

UpdateDivider=-1
DynamicVariables=1
Disabled=1

[MeasureDay1Summary]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=4
StringIndex2=2

Substitute="":"N/A"

[MeasureDay1Icon]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=4
StringIndex2=3

Substitute="#IconNames#"

[MeasureDay1TemperatureHighRAW]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=4
StringIndex2=4

Substitute="":"0"

[MeasureDay1TemperatureHigh]
Group=Processing
Measure=Calc
Formula=Round([#CurrentSection#RAW])

UpdateDivider=-1
DynamicVariables=1
Disabled=1

RegExpSubstitute=1 
Substitute="-0":"0"

[MeasureDay1TemperatureLowRAW]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=4
StringIndex2=5

Substitute="":"0"

[MeasureDay1TemperatureLow]
Group=Processing
Measure=Calc
Formula=Round([#CurrentSection#RAW])

UpdateDivider=-1
DynamicVariables=1
Disabled=1

RegExpSubstitute=1 
Substitute="-0":"0"

;================================================

[MeasureDay2Timestamp]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=5
StringIndex2=1

Substitute="":"0"

[MeasureDay2Weekday]
Group=Processing
Measure=Time

Timestamp=([MeasureDay2Timestamp]+#TimestampOffset#+[MeasureUTCOffset]*60*60)
Format=%A
FormatLocale=#Language#

UpdateDivider=-1
DynamicVariables=1
Disabled=1

[MeasureDay2WeekdayShort]
Group=Processing
Measure=Time

Timestamp=([MeasureDay2Timestamp]+#TimestampOffset#+[MeasureUTCOffset]*60*60)
Format=%a
FormatLocale=#Language#

UpdateDivider=-1
DynamicVariables=1
Disabled=1

[MeasureDay2Summary]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=5
StringIndex2=2

Substitute="":"N/A"

[MeasureDay2Icon]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=5
StringIndex2=3

Substitute="#IconNames#"

[MeasureDay2TemperatureHighRAW]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=5
StringIndex2=4

Substitute="":"0"

[MeasureDay2TemperatureHigh]
Group=Processing
Measure=Calc
Formula=Round([#CurrentSection#RAW])

UpdateDivider=-1
DynamicVariables=1
Disabled=1

RegExpSubstitute=1 
Substitute="-0":"0"

[MeasureDay2TemperatureLowRAW]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=5
StringIndex2=5

Substitute="":"0"

[MeasureDay2TemperatureLow]
Group=Processing
Measure=Calc
Formula=Round([#CurrentSection#RAW])

UpdateDivider=-1
DynamicVariables=1
Disabled=1

RegExpSubstitute=1 
Substitute="-0":"0"

;================================================

[MeasureDay3Timestamp]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=6
StringIndex2=1

Substitute="":"0"

[MeasureDay3Weekday]
Group=Processing
Measure=Time

Timestamp=([MeasureDay3Timestamp]+#TimestampOffset#+[MeasureUTCOffset]*60*60)
Format=%A
FormatLocale=#Language#

UpdateDivider=-1
DynamicVariables=1
Disabled=1

[MeasureDay3WeekdayShort]
Group=Processing
Measure=Time

Timestamp=([MeasureDay3Timestamp]+#TimestampOffset#+[MeasureUTCOffset]*60*60)
Format=%a
FormatLocale=#Language#

UpdateDivider=-1
DynamicVariables=1
Disabled=1

[MeasureDay3Summary]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=6
StringIndex2=2

Substitute="":"N/A"

[MeasureDay3Icon]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=6
StringIndex2=3

Substitute="#IconNames#"

[MeasureDay3TemperatureHighRAW]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=6
StringIndex2=4

Substitute="":"0"

[MeasureDay3TemperatureHigh]
Group=Processing
Measure=Calc
Formula=Round([#CurrentSection#RAW])

UpdateDivider=-1
DynamicVariables=1
Disabled=1

RegExpSubstitute=1 
Substitute="-0":"0"

[MeasureDay3TemperatureLowRAW]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=6
StringIndex2=5

Substitute="":"0"

[MeasureDay3TemperatureLow]
Group=Processing
Measure=Calc
Formula=Round([#CurrentSection#RAW])

UpdateDivider=-1
DynamicVariables=1
Disabled=1

RegExpSubstitute=1 
Substitute="-0":"0"

;================================================

[MeasureDay4Timestamp]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=7
StringIndex2=1

Substitute="":"0"

[MeasureDay4Weekday]
Group=Processing
Measure=Time

Timestamp=([MeasureDay4Timestamp]+#TimestampOffset#+[MeasureUTCOffset]*60*60)
Format=%A
FormatLocale=#Language#

UpdateDivider=-1
DynamicVariables=1
Disabled=1

[MeasureDay4WeekdayShort]
Group=Processing
Measure=Time

Timestamp=([MeasureDay4Timestamp]+#TimestampOffset#+[MeasureUTCOffset]*60*60)
Format=%a
FormatLocale=#Language#

UpdateDivider=-1
DynamicVariables=1
Disabled=1

[MeasureDay4Summary]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=7
StringIndex2=2

Substitute="":"N/A"

[MeasureDay4Icon]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=7
StringIndex2=3

Substitute="#IconNames#"

[MeasureDay4TemperatureHighRAW]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=7
StringIndex2=4

Substitute="":"0"

[MeasureDay4TemperatureHigh]
Group=Processing
Measure=Calc
Formula=Round([#CurrentSection#RAW])

UpdateDivider=-1
DynamicVariables=1
Disabled=1

RegExpSubstitute=1 
Substitute="-0":"0"

[MeasureDay4TemperatureLowRAW]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=7
StringIndex2=5

Substitute="":"0"

[MeasureDay4TemperatureLow]
Group=Processing
Measure=Calc
Formula=Round([#CurrentSection#RAW])

UpdateDivider=-1
DynamicVariables=1
Disabled=1

RegExpSubstitute=1 
Substitute="-0":"0"

;================================================

[MeasureDay5Timestamp]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=8
StringIndex2=1

Substitute="":"0"

[MeasureDay5Weekday]
Group=Processing
Measure=Time

Timestamp=([MeasureDay5Timestamp]+#TimestampOffset#+[MeasureUTCOffset]*60*60)
Format=%A
FormatLocale=#Language#

UpdateDivider=-1
DynamicVariables=1
Disabled=1

[MeasureDay5WeekdayShort]
Group=Processing
Measure=Time

Timestamp=([MeasureDay5Timestamp]+#TimestampOffset#+[MeasureUTCOffset]*60*60)
Format=%a
FormatLocale=#Language#

UpdateDivider=-1
DynamicVariables=1
Disabled=1

[MeasureDay5Summary]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=8
StringIndex2=2

Substitute="":"N/A"

[MeasureDay5Icon]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=8
StringIndex2=3

Substitute="#IconNames#"

[MeasureDay5TemperatureHighRAW]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=8
StringIndex2=4

Substitute="":"0"

[MeasureDay5TemperatureHigh]
Group=Processing
Measure=Calc
Formula=Round([#CurrentSection#RAW])

UpdateDivider=-1
DynamicVariables=1
Disabled=1

RegExpSubstitute=1 
Substitute="-0":"0"

[MeasureDay5TemperatureLowRAW]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=8
StringIndex2=5

Substitute="":"0"

[MeasureDay5TemperatureLow]
Group=Processing
Measure=Calc
Formula=Round([#CurrentSection#RAW])

UpdateDivider=-1
DynamicVariables=1
Disabled=1

RegExpSubstitute=1 
Substitute="-0":"0"

;================================================

[MeasureDay6Timestamp]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=9
StringIndex2=1

Substitute="":"0"

[MeasureDay6Weekday]
Group=Processing
Measure=Time

Timestamp=([MeasureDay6Timestamp]+#TimestampOffset#+[MeasureUTCOffset]*60*60)
Format=%A
FormatLocale=#Language#

UpdateDivider=-1
DynamicVariables=1
Disabled=1

[MeasureDay6WeekdayShort]
Group=Processing
Measure=Time

Timestamp=([MeasureDay6Timestamp]+#TimestampOffset#+[MeasureUTCOffset]*60*60)
Format=%a
FormatLocale=#Language#

UpdateDivider=-1
DynamicVariables=1
Disabled=1

[MeasureDay6Summary]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=9
StringIndex2=2

Substitute="":"N/A"

[MeasureDay6Icon]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=9
StringIndex2=3

Substitute="#IconNames#"

[MeasureDay6TemperatureHighRAW]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=9
StringIndex2=4

Substitute="":"0"

[MeasureDay6TemperatureHigh]
Group=Processing
Measure=Calc
Formula=Round([#CurrentSection#RAW])

UpdateDivider=-1
DynamicVariables=1
Disabled=1

RegExpSubstitute=1 
Substitute="-0":"0"

[MeasureDay6TemperatureLowRAW]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=9
StringIndex2=5

Substitute="":"0"

[MeasureDay6TemperatureLow]
Group=Processing
Measure=Calc
Formula=Round([#CurrentSection#RAW])

UpdateDivider=-1
DynamicVariables=1
Disabled=1

RegExpSubstitute=1 
Substitute="-0":"0"

;================================================

[MeasureDay7Timestamp]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=10
StringIndex2=1

Substitute="":"0"

[MeasureDay7Weekday]
Group=Processing
Measure=Time

Timestamp=([MeasureDay7Timestamp]+#TimestampOffset#+[MeasureUTCOffset]*60*60)
Format=%A
FormatLocale=#Language#

UpdateDivider=-1
DynamicVariables=1
Disabled=1

[MeasureDay7WeekdayShort]
Group=Processing
Measure=Time

Timestamp=([MeasureDay7Timestamp]+#TimestampOffset#+[MeasureUTCOffset]*60*60)
Format=%a
FormatLocale=#Language#

UpdateDivider=-1
DynamicVariables=1
Disabled=1

[MeasureDay7Summary]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=10
StringIndex2=2

Substitute="":"N/A"

[MeasureDay7Icon]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=10
StringIndex2=3

Substitute="#IconNames#"

[MeasureDay7TemperatureHighRAW]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=10
StringIndex2=4

Substitute="":"0"

[MeasureDay7TemperatureHigh]
Group=Processing
Measure=Calc
Formula=Round([#CurrentSection#RAW])

UpdateDivider=-1
DynamicVariables=1
Disabled=1

RegExpSubstitute=1 
Substitute="-0":"0"

[MeasureDay7TemperatureLowRAW]
Measure=WebParser
URL=[MeasureDarkSky]
RegExp=(?siU)#DayNRegExp#
StringIndex=10
StringIndex2=5

Substitute="":"0"

[MeasureDay7TemperatureLow]
Group=Processing
Measure=Calc
Formula=Round([#CurrentSection#RAW])

UpdateDivider=-1
DynamicVariables=1
Disabled=1

RegExpSubstitute=1 
Substitute="-0":"0"
