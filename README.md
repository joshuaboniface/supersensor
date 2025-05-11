# SuperSensor

**NOTICE:** In preparation for 2.x, this repository has been split into two
branches: `1.x` for the original 1.x hardware, and `2.x` for the updated 2.x
hardware. Please update your configurations to use the explicit `1.x` ref
for any 1.x hardware:

```
packages:
  joshuaboniface.supersensor: github://joshuaboniface/supersensor/supersensor.yaml@1.x
```

And ensure you check out the `1.x` branch to ensure correct updates going forward.

See the two branches here:

* [v1.x](https://github.com/joshuaboniface/supersensor/tree/v1.x)
* [v2.x](https://github.com/joshuaboniface/supersensor/tree/v2.x)

---

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

For more details, please [see my blog post on the SuperSensor project](https://www.boniface.me/the-supersensor/).
