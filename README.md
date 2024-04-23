# SuperSensor

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

To Use:

  * Install this ESPHome configuration to a compatible ESP32 devkit (below).
  * Install the ESP32 and sensors into the custom PCB.
  * [Optional] 3D Print a custom case (I haven't designed one yet, but contributions welcome).
  * Power up the SuperSensor, connect to the WiFi AP, and connect it to your network.
  * Install the SuperSensor somewhere that makes sense.
  * Add/adopt the SuperSensor to HomeAssistant using the automatic name.
  * Tune the SuperSensor values to your needs.

Note: Once programmed, the output LED will flash continuously until connected
      to HomeAssistant, and a bit longer to establish if the wake word
      functionality is enabled. This is by design, so you know if your sensors
      are connected or not. If you do not want this, comment out the
      `light.turn_on` block starting on line 54 of the ESPHome configuration
      to disable this functionality.

## Parts List

* 1x ESP32 devkit (V4 38-pin, slim) [AliExpress (HW-395)](https://www.aliexpress.com/item/1005006019875837.html)
* 1x INMP441 MEMS microphone [Amazon search](https://www.amazon.ca/s?k=INMP441)
* 1x BME680 temperature/humidity/pressure/gase sensor (3.3v models); BME280 or BMP280 can be subsistuted but with reduced fuctionality (comment/uncomment the appropriate blocks as needed) [AliExpress](https://www.aliexpress.com/item/4000818429803.html)
* 1x TSL2591 light sensor [AliExpress](https://www.aliexpress.com/item/1005005514391429.html)
* 1x HLK-LD2410C-P mmWave radar sensor [AliExpress (LD2410C-P)](https://www.aliexpress.com/item/1005006000579211.html)
* 1x SR602 PIR sensor [AliExpress](https://www.aliexpress.com/item/1005001572550300.html)
* 2x Common-cathod RGB LEDs [Amazon search](https://www.amazon.ca/s?k=5mm+RGB+LED+common+cathode)
* 1x Resistor for the common-cathod RGB LED @ 3.3v input (~33-1000Ω, depending on desired brightness and LEDs)
* 1x SuperSensor PCB board (see "board/supersensor.dxf" or "board/supersensor.easyeda.json")
* 1x 3D Printed case [Optional] 
* 1x 3D Printed diffuser cover [Optional] 

## Configurable Options

There are several UI-configurable options with the SuperSensor to help you
get the most out of the sensor for your particular usecase.

### Voice Control

The SuperSensor's voice functionality can be completely disabled if voice
support is not desired. This defeats most of the point of the SuperSensor,
but can be done if desired.

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
cleared when any of the sensors report clearered.

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
without light, for insance in a hallway where one might not want a late
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
