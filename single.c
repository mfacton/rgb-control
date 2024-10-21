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
    data.save_data = 0;
    // setting direct mode
    data.j_rgb_1.speedAndBrightnessFlags = 0x08;
    data.j_rgb_1.colorFlags = 0x80;
    data.j_pipe_1.speedAndBrightnessFlags = 0x2A;
    data.j_pipe_1.colorFlags = 0x80;
    data.j_pipe_2.speedAndBrightnessFlags = 0x2A;
    data.j_pipe_2.colorFlags = 0x80;
    data.j_rainbow_1.speedAndBrightnessFlags = 0x29;
    data.j_rainbow_1.colorFlags = 0x80;
    data.j_rainbow_1.cycle_or_led_num = 0x28;
    data.j_rainbow_2.speedAndBrightnessFlags = 0x29;
    data.j_rainbow_2.colorFlags = 0x80;
    data.j_rainbow_2.cycle_or_led_num = 0x28;
    data.j_corsair.fan_flags = 0x29;
    data.j_corsair.corsair_quantity = 0x00;
    data.j_corsair.padding[2] = 0x82;
    data.j_corsair.is_individual = 0x78;
    data.j_corsair_outerll120.speedAndBrightnessFlags = 0x28;
    data.j_corsair_outerll120.colorFlags = 0x80;
    data.on_board_led.effect = MSI_DIRECT_MODE;
    data.on_board_led.speedAndBrightnessFlags = 0x29 | SYNC_SETTING_JRGB;
    data.on_board_led.colorFlags = PER_LED_FULL_SYNC_MODE;
    data.on_board_led_1.speedAndBrightnessFlags = 0x28;
    data.on_board_led_1.colorFlags = 0x80;
    data.on_board_led_2.speedAndBrightnessFlags = 0x28;
    data.on_board_led_2.colorFlags = 0x80;
    data.on_board_led_3.speedAndBrightnessFlags = 0x28;
    data.on_board_led_3.colorFlags = 0x80;
    data.on_board_led_4.speedAndBrightnessFlags = 0x28;
    data.on_board_led_4.colorFlags = 0x80;
    data.on_board_led_5.speedAndBrightnessFlags = 0x28;
    data.on_board_led_5.colorFlags = 0x80;
    data.on_board_led_6.speedAndBrightnessFlags = 0x28;
    data.on_board_led_6.colorFlags = 0x80;
    data.on_board_led_7.speedAndBrightnessFlags = 0x28;
    data.on_board_led_7.colorFlags = 0x80;
    data.on_board_led_8.speedAndBrightnessFlags = 0x28;
    data.on_board_led_8.colorFlags = 0x80;
    data.on_board_led_9.speedAndBrightnessFlags = 0x28;
    data.on_board_led_9.colorFlags = 0x80;
    data.j_rgb_2.speedAndBrightnessFlags = 0x2A;
    data.j_rgb_2.colorFlags = 0x80;

    data.j_rainbow_1.effect = MSI_DIRECT_MODE;
    data.j_rainbow_1.cycle_or_led_num = 64;
    data.on_board_led.colorFlags = PER_LED_BASIC_SYNC_MODE;

    hid_send_feature_report(dev, (unsigned char*)&data, sizeof(data));

    struct FeaturePacket_PerLED_185 perLed;
    perLed.report_id = 0x53;
    perLed.hdr0 = 0x25;
    perLed.hdr1 = 0x04;
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
        memset(perLed.leds+index+8, 255, 3);
        hid_send_feature_report(dev, (unsigned char*)&perLed, sizeof(perLed));

        nanosleep(&ts, NULL);
    }

    // hid_send_feature_report(dev, (unsigned char*)&perLed, sizeof(perLed));

    // hid_send_feature_report(dev, (unsigned char*)&data, sizeof(data));

    hid_close(dev);
    hid_exit();
}

