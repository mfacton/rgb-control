#include "common.h"

#include <time.h>
#include <stdio.h>

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <hidapi/hidapi.h>

int main() {
    hid_init();
    hid_device *dev = hid_open(VENDOR, PRODUCT, NULL);

    struct FeaturePacket_185 data;
    hid_get_feature_report(dev, (unsigned char*)&data, sizeof(data));

    data.report_id = 0x52;
    data.on_board_led.colorFlags = 0x80 | SYNC_SETTING_ONBOARD;
    // end config

    struct Color color1 = {255, 0, 0};
    struct Color color2 = {0, 255, 0};
    enum Mode mode = ModeColorShift;
    enum Brightness brightness = Brightness100;
    enum Speed speed = SpeedMedium;
    bool rainbow = true;
    bool save = false;
    
    /////////////////////////////////////
    data.j_rainbow_1.color1 = color1;
    data.j_rainbow_1.color2 = color2;
    data.j_rainbow_1.effect = mode;
    data.j_rainbow_1.speedAndBrightnessFlags = (brightness << 2) | (speed & 0x03);
    data.j_rainbow_1.padding = 0;
    if (rainbow) {
        data.j_rainbow_1.colorFlags &= 0x7F;
    }else{
        data.j_rainbow_1.colorFlags |= 0x80;
    }

    if(mode > ModeLightning) {
        data.on_board_led.speedAndBrightnessFlags |= SYNC_SETTING_JRGB;
        data.on_board_led.colorFlags              |= (SYNC_SETTING_JPIPE1 | SYNC_SETTING_JPIPE2);
    } else {
        data.on_board_led.speedAndBrightnessFlags &= ~SYNC_SETTING_JRGB;
        data.on_board_led.colorFlags              &= ~(SYNC_SETTING_JPIPE1 | SYNC_SETTING_JPIPE2);
    }
    data.save_data = save;

    hid_send_feature_report(dev, (unsigned char*)&data, sizeof(data));

    hid_close(dev);
    hid_exit();
}

