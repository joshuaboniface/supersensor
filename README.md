# SuperSensor

SuperSensor is an all-in-one voice, motion, presence, temperature/humidity/
pressure, light, and BLE sensor, built on an ESP32 with ESPHome, and inspired
heavily by the EverythingSmartHome Everything Presence One sensor and the
HomeAssistant "$13 Voice Assistant" project.

Use SuperSensors around your house to provide HomeAssistant Voice Assist
interfaces with wake word detection, as well as other sensor detection options
as you want them.

Assist feedback is provided by a single common-cathode RGB LED. No speakers
or annoying TTS feedback here! With the optional 3D Printed case and a clear
diffuser insert, this LED can be turned into a sleek light bar on the bottom
of the unit for quick and easy confirmation of voice actions.

To Use:

  * Fill out a "secrets.yaml" for your environment.
  * Install this ESPHome configuration to a compatible ESP32 devkit (V4).
  * Install the ESP32 and sensors into the custom PCB.
  * [Optional] 3D Print our custom case.
  * Install the SuperSensor somewhere that makes sense.
  * Add the SuperSensor to HomeAssistant using the automatic name.

Note: Once programmed, the output LED will flash continuously until connected
      to HomeAssistant, and a bit longer to establish if the wake word
      functionality is enabled. This is by design, so you know if your sensors
      are connected or not. If you do not want this, comment out the
      `light.turn_on` block starting on line 29 of the ESPHome configuration
      to disable this functionality.

## Parts List

* 1x ESP32 devkit
* 1x Common-cathod RGB LED
* 1x Resistor for the common-cathod RGB LED @ 3.3v input (~33-1000Ω, depending on desired brightness and LED)
* 1x INMP441 MEMS microphone
* 1x BME280 temperature/humidity/pressure sensor (3.3v models)
* 1x VEML7700 light sensor
* 1x HLK-LD1115H-24G mmWave radar sensor
* 1x HC-SR501 (or similar) PIR sensor
