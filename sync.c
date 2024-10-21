#include "common.h"

#include <time.h>
#include <stdio.h>

#include <string.h>
#include <stdio.h>
#include <hidapi/hidapi.h>

int main() {
    hid_init();
    hid_device *dev = hid_open(VENDOR, PRODUCT, NULL);

    struct FeaturePacket_185 data;
    hid_get_feature_report(dev, (unsigned char*)&data, sizeof(data));
    printf("%d\n", data.j_rainbow_1.color1.b);

    data.report_id = 0x52;
    // setting direct mode
    data.j_rainbow_1.effect = ModeStatic;
    data.j_rainbow_1.cycle_or_led_num = SYNC_PER_LED_MODE_JRAINBOW_LED_COUNT;
    data.j_rainbow_1.speedAndBrightnessFlags = 0x29;
    data.j_rainbow_1.colorFlags = 0x80;
    data.j_rainbow_1.cycle_or_led_num = 62;

    data.on_board_led.effect = MSI_DIRECT_MODE;
    data.on_board_led.speedAndBrightnessFlags = 0x29 | SYNC_SETTING_JRGB;
    data.on_board_led.colorFlags = PER_LED_FULL_SYNC_MODE;

    hid_send_feature_report(dev, (unsigned char*)&data, sizeof(data));

    struct FeaturePacket_PerLED_185 perLed;
    perLed.report_id = 0x53;
    perLed.hdr0 = 0x25;
    perLed.hdr1 = 0x06;
    perLed.hdr2 = 0x00;
    perLed.hdr3 = 0x00;

    memset(perLed.leds, 0, sizeof(perLed.leds));
    perLed.leds[8].g = 255;
    memset(perLed.leds+8, 255, sizeof(perLed.leds[0]));
    memset(perLed.leds+8, 255, sizeof(perLed.leds[0]));

    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 50000000; //0.05

    int index = 0;
    while (1) {
        index++;
        index %= 9;

        memset(perLed.leds, 0, sizeof(perLed.leds));
        memset(perLed.leds+index+8, 255, sizeof(perLed.leds[0]));
        hid_send_feature_report(dev, (unsigned char*)&perLed, sizeof(perLed));

        nanosleep(&ts, NULL);
    }

    // hid_send_feature_report(dev, (unsigned char*)&perLed, sizeof(perLed));

    // hid_send_feature_report(dev, (unsigned char*)&data, sizeof(data));

    hid_close(dev);
    hid_exit();
}

