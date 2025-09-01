# SuperSensor v1.x

**NOTICE: This is the previous version of the SuperSensor, v1.x. This has been superceded by [version 2.x](https://github.com/joshuaboniface/supersensor2), which features numerous improvements in the PCB design, components, and code functionality. Use this code only if you are running the previous revision of the board; new users should see the updated link above and the [current version of the blog post](https://www.boniface.me/posts/the-supersensor-2.0/).**

SuperSensor is an all-in-one voice, motion, presence, temperature/humidity/
pressure, and light sensor, built on an ESP32 with ESPHome, and inspired
heavily by the EverythingSmartHome Everything Presence One sensor and the
HomeAssistant "$13 Voice Assistant" project.

Use SuperSensors around your house to provide HomeAssistant Voice Assist
interfaces with wake word detection, as well as other sensor detection options
as you want them.

Assist feedback is provided by a pair of common-cathode RGB LED. No speakers
or annoying TTS feedback here! With an optional 3D Printed case and a clear
diffuser cover, the LEDs can be turned into a sleek light bar on the bottom
of the unit for quick and easy confirmation of voice actions, or just use
it bare if you like the "PCB on a wall" aesthetic.

For more details, please [see my blog post on the SuperSensor project](https://www.boniface.me/posts/the-supersensor/).

## Parts List

* 1x ESP32 devkit (V4 38-pin, slim) [AliExpress (HW-395)](https://www.aliexpress.com/item/1005006019875837.html)
* 1x INMP441 MEMS microphone [Amazon search](https://www.amazon.ca/s?k=INMP441)
* 1x BME680 temperature/humidity/pressure/gas sensor (3.3v models); BME280 or BMP280 can be substituted but with reduced functionality (comment/uncomment the appropriate blocks as needed) [AliExpress](https://www.aliexpress.com/item/4000818429803.html)
* 1x TSL2591 light sensor [AliExpress](https://www.aliexpress.com/item/1005005514391429.html)
* 1x HLK-LD2410C-P mm-Wave radar sensor [AliExpress (LD2410C-P)](https://www.aliexpress.com/item/1005006000579211.html)
* 1x SR602 PIR sensor [AliExpress](https://www.aliexpress.com/item/1005001572550300.html)
* 2x Common-cathode RGB LEDs [Amazon search](https://www.amazon.ca/s?k=5mm+RGB+LED+common+cathode)
* 1x Resistor for the common-cathode RGB LED @ 3.3v input (~33-1000Ω, depending on desired brightness and LEDs)
* 1x SuperSensor PCB board (see "board/supersensor.dxf" or "board/supersensor.easyeda.json")
* 1x 3D Printed case [Optional] 
* 1x 3D Printed diffuser cover [Optional] 

## Configurable Options

There are several UI-configurable options with the SuperSensor to help you
get the most out of the sensor for your particular use-case.

### Voice Control

The SuperSensor's voice functionality can be completely disabled if voice
support is not desired. This defeats most of the point of the SuperSensor,
but can be done if desired.

### Gas Ceiling

The AQ (air quality) calculation from the BME680 requires a "maximum"/ceiling
threshold for the gas resistance value in clean air after some operation
time. The value defaults to 200 kΩ to provide an initial baseline, but
should be calibrated manually after setup as each sensor is different. See
the section "Calibrating AQ" below for more details.

### Light Threshold Control

The SuperSensor features a "light presence" binary sensor based on the light
level reported by the TSL2591 sensor. This control defines the minimum lux
value from the sensor to be considered "presence". For instance, if you have
a room that is usually dark at 0-5 lux, but illuminated to 100 lux when a
(non-automated) light switch is turned on, you could set a threshold here
of say 30 lux: then, while the light is on, "light presence" is detected,
and when the light is off, "light presence" is cleared. Light presence can
be used standalone or as part of the integrated occupancy sensor (below).

Valid range is 0 lux (always on) to 200 lux, in 5 lux increments.
Default value is 30 lux.

### PIR Hold Time

The SuperSensor uses an SR602 PIR sensor, which has a stock hold time of 2.5
seconds. While this is configurable via a resistor, this is cumbersome.
Instead, the SuperSensor features a PIR Hold Time control, which allows you
to set how long you want a PIR trigger to be "held" on. Each new trigger of
the PIR resets the timer, so as long as a PIR event fires at least this
often, the "PIR presence" sensor will remain detected.

Valid range is 0 seconds (match PIR) to 60 seconds, in 5 second increments.
Default value is 15 seconds.

### Integrated Occupancy Sensor

The SuperSensor features a fully integrated "occupancy" sensor, which can be
configured to provide exactly the sort of occupancy detection you may want
for your room.

There are 7 options (plus "None"/disabled), with both "detect" and "clear"
handled separately:

#### PIR + Radar + Light

Occupancy is detected when all 3 sensors report detected, and occupancy is
cleared when any of the sensors report cleared.

For detect, this provides the most "safety" against misfires, but requires
a normally-dark room with a non-automated light source and clear PIR
detection positioning.

For clear, this option is probably not very useful as it is likely to clear
quite frequently from the PIR, but is provided for completeness.

#### PIR + Radar

Occupancy is detected when both sensors report detected, and occupancy is
cleared when either of the sensors report cleared.

For detect, this provides good "safety" against PIR misfires without
needing a normally-dark room, though detection may be slightly delayed
from either sensor.

For clear, this option is probably not very useful as it is likely to clear
quite frequently from the PIR, but is provided for completeness.

#### PIR + Light

Occupancy is detected when both sensors report detected, and occupancy is
cleared when either of the sensors report cleared.

For detect, this provides some "safety" against PIR misfires, but requires
a normally-dark room with a non-automated light source and clear PIR
detection positioning.

For clear, this option is probably not very useful as it is likely to clear
quite frequently from the PIR, but is provided for completeness.

#### Radar + Light

Occupancy is detected when both sensors report detected, and occupancy is
cleared when either of the sensors report cleared.

For detect, this allows for radar detection while suppressing occupancy
without light, for instance in a hallway where one might not want a late
night bathroom visit to turn on the lights, or something to that effect.

For clear, this option can provide a useful option to clear presence
quickly if the lights go out, while still providing Radar presence.

#### PIR Only

Occupancy is based entirely on the PIR sensor for both detect and clear.

Prone to misfires, but otherwise a good option for quick detection and
clearance in a primarily-moving zone (e.g. hallway).

#### Radar Only

Occupancy is based entirely on the Radar sensor for both detect and clear.

Useful for an area with no consistent motion or light level.

#### Light Only

Occupancy is based entirely on the Light sensor for both detect and clear.

Useful for full dependence on an external light source.

#### None

Disable the functionality in either direction.

For detect, no occupancy will ever fire.

For clear, no states will clear occupancy; with any detect option, this
means that occupancy will be detected only once and never clear, which
is likely not useful.

## Calibrating AQ

The Supersensor uses the Bosch BME680 combination temperature, humidity,
pressure, and gas sensor to provide a wide range of useful information about
the environmental conditions the sensor is placed in. However, this sensor
can be tricky to work with.

While it's normally recommended to use the Bosch BSEC library with this
sensor, in my ~6 month experience I found this library to be far more trouble
than it was worth. Specifically, it's IAQ measurement is nearly useless, with
a strong tendency to get stuck in an upward trend constantly "calibrating"
itself to higher and higher baselines, to the point where nonsensical values
were being read. After much research into this, I decided to abandon the
library in version 1.1 and went with a more custom solution.

Instead of the BSEC, we use the stock BME680 ESPHome library, along with
some calculations by thstielow on GitHub in their [IAQ project](https://github.com/thstielow/raspi-bme680-iaq).
This provided some useful example code and formulae to calculate a useful
Air Quality (AQ) value instead of the useless Bosch value.

However using this method requires some manual calibration of the sensor
after putting it together but before final use, in order to get a somewhat
accurate value out of the AQ component. If you don't care about the AQ value,
you can skip this, but it is recommended to take full advantage of the sensor.

As a quick explainer, the code leverages a combination of the "Gas Resistance"
value provided by the sensor, along with an absolute humidity calculated from
the temperature and relative humidity of the sensor (included ESPHome sensor),
along with two values (one configurable, one hard-coded) and several formulae
to arrive at the resulting AQ value. For full details of the calculation,
see the repository linked above, which was re-implemented faithfully here.

The first thing to note is that each BME680 sensor is wildly different in
terms of gas resistance values. In the same air, I had sensors reading values
that differed by nearly 200,000Ω, which necessitates a human-configurable
baseline value. Further, the IAQ project recommends determining a linear
slope value for this, but instead of trying to explain how to calculate this,
I just went with the default slope value of 0.03 for this first iteration.

Thus, the main difficulty in getting a useful AQ score is finding the
"Gas Resistance Ceiling" value. This value is configurable in the
SuperSensor interface (Web or HomeAssistant), and should be calibrated as
follows during the initial setup of the supersensor.

1. Find a known-clean room, for instance a well-ventilated, well-cleaned
room in your house or similar. It should have fresh air (no stray VOCs) but
also minimal drafts or outside exposure especially if there is a poor external
AQ level. This will be your calibration reference room. Ideally, this room
should be somewhere between 16C and 26C for optimal performance, so air
conditioning (or a nice spring/fall day) is best.

2. Turn on the SuperSensor in this environment, and connect it to your
HomeAssistant instance; this will be critical for viewing historical graphs
during the following steps.

3. Let the SuperSensor run to "burn in" the gas sensor for at least 3-6 hours,
or until the value for the Gas Resistance stabilizes. It is best to avoid much
movement or activity in the selected calibration room to avoid disrupting
the sensor during this time. It is also best to ensure that the ambient
temperature changes as little as possible during this time.

4. Review the resulting graph of Gas Resistance over the burn-in period. You
can usually ignore the first hour or two as the sensor was burning in, and
focus instead on the last hour or so.

5. Make note of the highest mean value reached by the sensor during this time.
This will be your baseline value for calibrating the Gas Resistance Ceiling.

6. Round the value up to the nearest 1000. For example, if the maximum value
was 195732.1, round this to 196000.0.

7. Find the difference in the temperature of the BME680 temperature sensor
from 20C, called ΔT below. I found this part by trial-and-error, so this is
not precise, but as an example if the calibration room is reporting 26C, your
ΔT value in the next step is 6. If your temperature was below 20C, use 0.

8. Use one of the following formulae to come up with your offset value, which
depends on the maximum value range found in step 6.

   * `<100,000`: 200 * ΔT = 0-1200
   * `100,000-200,000`: 500 * ΔT = 0-3000
   * `>200,000`: 1000 * ΔT = 0-6000

Again this value is rough, and might not even really be needed, but helps
avoid weird issues with AQ values dropping suddenly later as temperature
and humidity changes.

9. Add your offset value from step 8 to the rounded maximum from step 6.
For example, 196000.0 with a ΔT of 5C (25C ambient) yields 201000.0

10. Divide the result from 9 by 1000 to give a number from 1-500. This
is the value to enter as the "Gas Resistance Ceiling (kΩ)" for this
sensor. This value will be saved in the NV-RAM of the ESP32 and preserved
on reboots.

At this point, you should have a value that results in the "BME680 AQ"
sensor reporting 100% AQ, i.e. clean air. You can now test to ensure
that the value will correctly drop as VOCs are added.

1. Take a Sharpie permanent marker, Acetone nail polish remover, or some
other VOC that the BME680 gas sensor can detect, and place it near the
sensor. For example with a sharpie, remove the cap and place the tip
about 1-2cm from the sensor, or place a small capful of nail polish
remover about 3-5cm from the sensor.

2. Wait about 30 seconds.

3. You should see the AQ value drop precipitously, into the order of 50%
or lower, and ideally closer to 0-20%. If the value remains higher than
50% with this test, your calculated Gas Resistance Ceiling might be
too low, and should be increased in increments of 1000.

4. Remove the VOC source (replace the cap, remove the capful of remover,
etc.) and wait about 30-60 minutes.

5. You should see the AQ value and gas resistance return to their original
values. If it is significantly lower than before, even after waiting 60+
minutes, restart the calculation from step 5 in the previous section
using this new value as the baseline.

At this point, the sensor should be calibrated enough for day-to-day
casual home use, and will tell you if there is any significant
VOC contamination in the air by dropping the AQ value from 100% to some
lower value representing the approximate decrease in air quality. Since
the sensor also factors in the absolute humidity (and via that, the
ambient temperature) into the AQ calculation, high humidity will also
drop the value, as this too impacts the air quality. Hopefully this
is useful for your purposes.

If you find that the AQ value still doesn't represent known reality,
you can also tweak the in-code value for `ph_slope` on line 522, as
it's possible your sensor differs significantly here. As mentioned
above this is still a work in progress to determine for myself, so
future versions may alter this or include calibration of this value
automatically, depending on how things go in my testing.
>>>>>>> v1.x
