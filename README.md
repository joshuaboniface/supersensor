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
      `light.turn_on` block starting on line 38 of the ESPHome configuration
      to disable this functionality.

For more details, please [see my blog post on the SuperSensor project](https://www.boniface.me/the-supersensor/).

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

## AQ Calibration Process

The Supersensor uses the Bosch BME680 combination temperature, humidity,
pressure, and gas sensor to provide a wide range of useful information about
the environmental conditions the sensor is placed in. However, this sensor
can be tricky to work with.

While it's normally recommended to use the Bosch BSEC library with this
sensor, this library has two major defects:

* It is not compatable with the ESP-IDF ESPHome framework, which is required
for various other components (mostly, the voice subsystem).

* In my experience with the library, I found it to become wildly inaccurate
as time went on, with the sensor constantly recalibrating upwards and upwards
until it was reading values of 500+ AQ in my interior rooms.

To avoid both issues, the Supersensor leverages the approximation calculations
from https://github.com/thstielow/raspi-bme680-iaq, along with a bit of
experimentation, to provide a much more reliable experience, including an
integrated, guided calibration process.

The calibration process involves several steps with defined times between them,
and you will need the following items to simulate both a higher humidity to
calculate a humidity slope, and a simulated VOC to calibrate the sensor:

* A portable device (Phone, etc.) showing the Supersensor sensor details in
  Homeassistant to track the progress.
* A spray mister containing clean water (tap or distilled).
* Isopropyl Alcohol (IPA, rubbing alcohol), between 70% and 99%.
* A piece of paper towel and possibly tape to hold it.

Note that you must prepare and work fast while following the directions from
the "BME680 AQ Calibration Status" sensor during calibration.

1. Place the sensor in a known-clean (or as clean as possible) air environment.

   If possible, place the sensor in an open room without human habitation, near
   an open window or air purifier, and leave it there for at least 30 minutes
   without disturbing it.

2. When ready, before re-entering the area of the sensor, activate the "BME680
IAQ Calibration" switch.

   This will immediately take the "clean air" reading, and you will have 30s
   before the next stage.

   The calibration status sensor will show `Clean Air Snapshot (30s)` when
   ready to proceed.

3. Prepare your mist bottle for spraying while the sensor captures its initial
humidity reading.

   The calibration status sensor will briefly show `Capturing Initial Humidity`
   and then `Spray Water Mist Near Sensor (30s)` when ready to proceed.

3. Spray a mist of water about 15cm in front of the sensor. Take care not to
directly spray the sensor; spray perpendicular to it.

   You will have 30s to do this, after which the sensor will begin capturing
   the humidity value.

   The calibration sensor will show `Wait for Maximum Humidity` when ready to
   proceed.

4. Wait for the maximum humidity to be captured and subsequently dissapate.

   The calibration status sensor will show `Wait for Humitity to Dissipate
   (120s)` when ready to proceed.

5. Prepare your IPA paper towel by blotting a small amount of IPA onto a corner
of the paper towel; do this only after "Wait for Humidity to Dissipate (120s)"
is being shown.

    The calibration sensor will show `Expose Sensor to IPA (300s)` when ready
    to proceed.

6. Place your IPA-containing paper towel about 5-10cm below and in front of the
BME680 sensor and leave it there for 5 minutes until prompted; taping it to
the wall, cord, etc. might be helpful here.

    The calibration sensor will show `Wait for Minimum Gas Resistance` when
    ready to proceed.

7. Remove the IPA-containing paper towel and exit the room with it. The manual
portion of the calibration is now done.

    The calibration sensor will show `Wait for Return to Baseline` when ready
    to proceed.

8. It is now important not to disturb the sensor for at least 1-2 hours while
the IPA fumes dissipate and it recovers back to the baseline clean air level.
This includes not re-entering the room or otherwise adjusting the Supersensor
(e.g. powercycling it or moving it).

    The calibration sensor will show `Calibration Completed and Saved` when
    ready to proceed.

9. The sensor is now calibrated and the "BME680 AQ Last Calibration" sensor
will update to show the current time. You can now re-enter the room.

If the calibration becomes "stuck" during step 8 for more than 3-4 hours, you
may have a bad calibration; this just happens sometimes. Cancel the calibration
by disabling the switch, wait some more time for the "BME680 Current Gas
Resistance" sensor to normalize and level out, and then try again.

For added benefit, several diagnostic category sensors are provided to show the
values obtained from the last calibration. You can use these to see how close
your calibration is to reality over time. Note that the actual AQ calculation
discards the top 10% of the range (i.e. the 100% clean value is considered to
be 90% of the detected maximum to provide wiggle room for normal habitation
conditions) and it takes the absolute humidity into account, so humidity
changes will affect the AQ value.

Once calibrated, you should not need to recalibrate for quite a while; the
sensor provides a "BME680 Last Calibration" datetime value sensor showing when
it was last calibrated. Recalibrate only if you notice you need it (i.e.
readings become inaccurate) or if you move the sensor somewhere else.

A future planned major revision of the Supersensor (2.0) will discard the
BME680 in favour of alternate sensors, but for now this is the best we can do,
because I can't justify replacing my 9 Supersensors!

## Supersensor Dashboard

If you have several Supersensors, you may find this dashboard handy. It
provides a convenient way to show multiple Supersensors in a standard way, with
all the relevant sensors and configuration values available.

To use this dashboard, create a new Dashboard and paste the following YAML into
it. You can then add your individual Supersensors by their MAC ID, and then
duplicate the view for each sensor, replacing the `supersensor_id` with the
MAC ID of your individual Supersensors.

This dashboard requires the [Decluttering Card custom card](https://github.com/custom-cards/decluttering-card)
to function properly.

Some of these sensors are custom templates. For instance, "Device Location" is
crafted based on what I name the Supersensors during adoption, using this
sensor template:

```
{{ device_attr('binary_sensor.supersensor_24ac2c_supersensor_occupancy', 'name')|replace('Supersensor 24ac2c ', '') }}
```

Which will show something like "Joshua's Bedroom" or "Garage".

Similarly, to avoid exposing the "internal" voice support switch, "Voice
Support State" is a template binary sensor with the "Running" show-as device
class to report its state:

```
{{ states('switch.supersensor_24ac2c_voice_support_active') }}
```

Once added, you can easily add (or remove) Supersensors from the dashboard, or
adjust what you want to see in the dashboard by adjusting the decluttering
template values as you see fit.

### Raw YAML Dashboard

```
```
