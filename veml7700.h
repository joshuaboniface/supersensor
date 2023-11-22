#include "esphome.h"
#include <Adafruit_VEML7700.h>

// Requires this lib installed: $ platformio lib --global install "Adafruit BusIO"
// based on https://github.com/adafruit/Adafruit_VEML7700/blob/master/examples/veml7700_test/veml7700_test.ino

class VEML7700CustomSensor : public PollingComponent, public Sensor {
    public:
        Adafruit_VEML7700 veml = Adafruit_VEML7700();

    Sensor *lux_sensor = new Sensor();

    VEML7700CustomSensor() : PollingComponent(5000) {}
    void setup() override {
        Wire.begin();
        veml.begin();
        veml.setGain(VEML7700_GAIN_1);
        veml.setIntegrationTime(VEML7700_IT_800MS);
        // veml.powerSaveEnable(true);
        // veml.setPowerSaveMode(VEML7700_POWERSAVE_MODE4);
        // veml.setLowThreshold(10000);
        // veml.setHighThreshold(20000);
        // veml.interruptEnable(true);
    }

    void update() override {
        float lux = veml.readLux();
        ESP_LOGD("VEML7700", "The value of sensor lux is: %.0f", lux);
        lux_sensor->publish_state(lux);
    }
};
