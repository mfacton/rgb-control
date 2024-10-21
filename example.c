#include <stdio.h>
#include <stdlib.h>
#include <hidapi/hidapi.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>

enum MSI_ZONE
{
    MSI_ZONE_NONE                   = 0,
    MSI_ZONE_J_RGB_1                = 1,
    MSI_ZONE_J_RGB_2                = 2,
    MSI_ZONE_J_PIPE_1               = 3,
    MSI_ZONE_J_PIPE_2               = 4,
    MSI_ZONE_J_RAINBOW_1            = 5,
    MSI_ZONE_J_RAINBOW_2            = 6,
    MSI_ZONE_J_RAINBOW_3            = 7,
    MSI_ZONE_J_CORSAIR              = 8,
    MSI_ZONE_J_CORSAIR_OUTERLL120   = 9,
    MSI_ZONE_ON_BOARD_LED_0         = 10,
    MSI_ZONE_ON_BOARD_LED_1         = 11,
    MSI_ZONE_ON_BOARD_LED_2         = 12,
    MSI_ZONE_ON_BOARD_LED_3         = 13,
    MSI_ZONE_ON_BOARD_LED_4         = 14,
    MSI_ZONE_ON_BOARD_LED_5         = 15,
    MSI_ZONE_ON_BOARD_LED_6         = 16,
    MSI_ZONE_ON_BOARD_LED_7         = 17,
    MSI_ZONE_ON_BOARD_LED_8         = 18,
    MSI_ZONE_ON_BOARD_LED_9         = 19,
    MSI_ZONE_ON_BOARD_LED_10        = 20
};

enum MSI_MODE
{
    MSI_MODE_DISABLE                    = 0,
    MSI_MODE_STATIC                     = 1,
    MSI_MODE_BREATHING                  = 2,
    MSI_MODE_FLASHING                   = 3,
    MSI_MODE_DOUBLE_FLASHING            = 4,
    MSI_MODE_LIGHTNING                  = 5,
    MSI_MODE_MSI_MARQUEE                = 6,
    MSI_MODE_METEOR                     = 7,
    MSI_MODE_WATER_DROP                 = 8,
    MSI_MODE_MSI_RAINBOW                = 9,
    MSI_MODE_POP                        = 10,
    MSI_MODE_RAP                        = 11,
    MSI_MODE_JAZZ                       = 12,
    MSI_MODE_PLAY                       = 13,
    MSI_MODE_MOVIE                      = 14,
    MSI_MODE_COLOR_RING                 = 15,
    MSI_MODE_PLANETARY                  = 16,
    MSI_MODE_DOUBLE_METEOR              = 17,
    MSI_MODE_ENERGY                     = 18,
    MSI_MODE_BLINK                      = 19,
    MSI_MODE_CLOCK                      = 20,
    MSI_MODE_COLOR_PULSE                = 21,
    MSI_MODE_COLOR_SHIFT                = 22,
    MSI_MODE_COLOR_WAVE                 = 23,
    MSI_MODE_MARQUEE                    = 24,
    MSI_MODE_RAINBOW                    = 25,
    MSI_MODE_RAINBOW_WAVE               = 26,
    MSI_MODE_VISOR                      = 27,
    MSI_MODE_JRAINBOW                   = 28,
    MSI_MODE_RAINBOW_FLASHING           = 29,
    MSI_MODE_RAINBOW_DOUBLE_FLASHING    = 30,
    MSI_MODE_RANDOM                     = 31,
    MSI_MODE_FAN_CONTROL                = 32,
    MSI_MODE_DISABLE_2                  = 33,
    MSI_MODE_COLOR_RING_FLASHING        = 34,
    MSI_MODE_COLOR_RING_DOUBLE_FLASHING = 35,
    MSI_MODE_STACK                      = 36,
    MSI_MODE_CORSAIR_QUE                = 37,
    MSI_MODE_FIRE                       = 38,
    MSI_MODE_LAVA                       = 39,
    MSI_MODE_DIRECT_DUMMY               = 100
};

enum MSI_SPEED
{
    MSI_SPEED_LOW                       = 0,
    MSI_SPEED_MEDIUM                    = 1,
    MSI_SPEED_HIGH                      = 2,
};

enum MSI_FAN_TYPE
{
    MSI_FAN_TYPE_SP                     = 0,
    MSI_FAN_TYPE_HD                     = 1,
    MSI_FAN_TYPE_LL                     = 2,
};

enum MSI_BRIGHTNESS
{
    MSI_BRIGHTNESS_OFF                  = 0,
    MSI_BRIGHTNESS_LEVEL_10             = 1,
    MSI_BRIGHTNESS_LEVEL_20             = 2,
    MSI_BRIGHTNESS_LEVEL_30             = 3,
    MSI_BRIGHTNESS_LEVEL_40             = 4,
    MSI_BRIGHTNESS_LEVEL_50             = 5,
    MSI_BRIGHTNESS_LEVEL_60             = 6,
    MSI_BRIGHTNESS_LEVEL_70             = 7,
    MSI_BRIGHTNESS_LEVEL_80             = 8,
    MSI_BRIGHTNESS_LEVEL_90             = 9,
    MSI_BRIGHTNESS_LEVEL_100            = 10,
};

struct Color
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

struct CorsairZoneData
{
    unsigned char effect                    ;//= MSI_MODE_STATIC;
    struct Color         color                     ;//{ 0, 0, 0 };
    unsigned char fan_flags                 ;//= 40;
    unsigned char corsair_quantity          ;//= 0;
    unsigned char padding[4]                ;//= { 0, 0, 0, 0 };
    unsigned char is_individual             ;//= 0;
};

struct ZoneData
{
    unsigned char effect                   ;// = MSI_MODE_STATIC;
    struct Color         color              ;//       { 0, 0, 0 };
    unsigned char speedAndBrightnessFlags  ;// = 0;
    struct Color         color2             ;//       { 0, 0, 0 };
    unsigned char colorFlags               ;// = 0;
    unsigned char padding                  ;// = 0;
};

struct RainbowZoneData
{
    unsigned char effect                   ;// = MSI_MODE_STATIC;
    struct Color         color               ;//      { 0, 0, 0 };
    unsigned char speedAndBrightnessFlags  ;// = 0;
    struct Color         color2             ;//       { 0, 0, 0 };
    unsigned char colorFlags               ;// = 0;
    unsigned char padding                  ;// = 0;
    unsigned char cycle_or_led_num         ;// = 100;
};

struct FeaturePacket_185
{
    const unsigned char report_id           ;//= 0x52; // Report ID
    struct ZoneData            j_rgb_1;                    // 1
    struct ZoneData            j_pipe_1;                   // 11
    struct ZoneData            j_pipe_2;                   // 21
    struct RainbowZoneData     j_rainbow_1;                // 31
    struct RainbowZoneData     j_rainbow_2;                // 42
    struct CorsairZoneData     j_corsair;                  // 53
    struct ZoneData            j_corsair_outerll120;       // 64
    struct ZoneData            on_board_led;               // 74
    struct ZoneData            on_board_led_1;             // 84
    struct ZoneData            on_board_led_2;             // 94
    struct ZoneData            on_board_led_3;             // 104
    struct ZoneData            on_board_led_4;             // 114
    struct ZoneData            on_board_led_5;             // 124
    struct ZoneData            on_board_led_6;             // 134
    struct ZoneData            on_board_led_7;             // 144
    struct ZoneData            on_board_led_8;             // 154
    struct ZoneData            on_board_led_9;             // 164
    struct ZoneData            j_rgb_2;                    // 174
    unsigned char       save_data          ;// = 0;    // 184
};

void printColor(const struct Color* color) {
    printf("Color (R: %d, G: %d, B: %d)\n", color->R, color->G, color->B);
}

// Function to print the ZoneData structure
void printZoneData(const struct ZoneData* zone) {
    printf("  Effect: %d\n", zone->effect);
    printColor(&zone->color);
    printf("  Speed & Brightness Flags: %d\n", zone->speedAndBrightnessFlags);
    printColor(&zone->color2);
    printf("  Color Flags: %d\n", zone->colorFlags);
    printf("  Padding: %d\n", zone->padding);
}

// Function to print the RainbowZoneData structure
void printRainbowZoneData(const struct RainbowZoneData* rainbow) {
    printf("  Effect: %d\n", rainbow->effect);
    printColor(&rainbow->color);
    printf("  Speed & Brightness Flags: %d\n", rainbow->speedAndBrightnessFlags);
    printColor(&rainbow->color2);
    printf("  Color Flags: %d\n", rainbow->colorFlags);
    printf("  Padding: %d\n", rainbow->padding);
    printf("  Cycle or LED Number: %d\n", rainbow->cycle_or_led_num);
}

// Function to print the CorsairZoneData structure
void printCorsairZoneData(const struct CorsairZoneData* corsair) {
    printf("  Effect: %d\n", corsair->effect);
    printColor(&corsair->color);
    printf("  Fan Flags: %d\n", corsair->fan_flags);
    printf("  Corsair Quantity: %d\n", corsair->corsair_quantity);
    printf("  Is Individual: %d\n", corsair->is_individual);
    printf("  Padding: ");
    for (int i = 0; i < sizeof(corsair->padding); i++) {
        printf("%d ", corsair->padding[i]);
    }
    printf("\n");
}

// Function to print the FeaturePacket_185 structure
void printFeaturePacket(const struct FeaturePacket_185* packet) {
    printf("Feature Packet Details:\n");
    printf("  Report ID: %d\n", packet->report_id);
    printf("\n");
    printf("  j_rgb_1:\n");
    printZoneData(&packet->j_rgb_1);
    printf("\n");
    printf("  j_pipe_1:\n");
    printZoneData(&packet->j_pipe_1);
    printf("\n");
    printf("  j_pipe_2:\n");
    printZoneData(&packet->j_pipe_2);
    printf("\n");
    printf("  j_rainbow_1:\n");
    printRainbowZoneData(&packet->j_rainbow_1);
    printf("\n");
    printf("  j_rainbow_2:\n");
    printRainbowZoneData(&packet->j_rainbow_2);
    printf("\n");
    printf("  j_corsair:\n");
    printCorsairZoneData(&packet->j_corsair);
    printf("\n");
    printf("  j_corsair_outerll120:\n");
    printZoneData(&packet->j_corsair_outerll120);
    printf("\n");
    printf("  On-board LED:\n");
    printZoneData(&packet->on_board_led);
    printf("\n");
    printf("  On-board LED:\n");
    printZoneData(&packet->on_board_led_1);
    printf("\n");
    printf("  On-board LED:\n");
    printZoneData(&packet->on_board_led_2);
    printf("\n");
    printf("  On-board LED:\n");
    printZoneData(&packet->on_board_led_3);
    printf("\n");
    printf("  On-board LED:\n");
    printZoneData(&packet->on_board_led_4);
    printf("\n");
    printf("  On-board LED:\n");
    printZoneData(&packet->on_board_led_5);
    printf("\n");
    printf("  On-board LED:\n");
    printZoneData(&packet->on_board_led_6);
    printf("\n");
    printf("  On-board LED:\n");
    printZoneData(&packet->on_board_led_7);
    printf("\n");
    printf("  On-board LED:\n");
    printZoneData(&packet->on_board_led_8);
    printf("\n");
    printf("  On-board LED:\n");
    printZoneData(&packet->on_board_led_9);
    printf("\n");
    // Print other on-board LEDs similarly...
    printf("  Save Data: %d\n", packet->save_data);
}

int main() {
    setlocale(LC_ALL, "");

    //unsigned char data[65]; // Buffer to send and receive data

    //use lsusb to get this
    unsigned short vendor_id = 0x1462;
    unsigned short product_id = 0x7c95;

    // Initialize the HIDAPI library
    int res = hid_init();
    if (res != 0) {
        fprintf(stderr, "Failed to initialize HIDAPI library\n");
        return 1;
    }

    // Open the device
    hid_device *dev = hid_open(vendor_id, product_id, NULL);
    if (!dev) {
        fprintf(stderr, "Unable to open the device\n");
        hid_exit();
        return 1;
    }

    wchar_t tname[256];
    hid_get_manufacturer_string(dev, tname, 256);

    // wprintf(L"Name: %ls\n", tname);

    ////////// read FW version ///////////////
    unsigned char request[64];
    unsigned char response[64];
    int ret_val = 64;
    printf("APROM\n");

    /*-----------------------------------------------------*\
    | First read the APROM                                  |
    | Checksum also available at report ID 180, with MSB    |
    | stored at index 0x08 and LSB at 0x09                  |
    \*-----------------------------------------------------*/

    /*-----------------------------------------------------*\
    | Zero out buffers                                      |
    \*-----------------------------------------------------*/
    memset(request, 0x00, sizeof(request));
    memset(response, 0x00, sizeof(response));

    /*-----------------------------------------------------*\
    | Set up APROM Firmware Version Request packet          |
    \*-----------------------------------------------------*/
    request[0x00]   = 0x01;
    request[0x01]   = 0xB0;

    /*-----------------------------------------------------*\
    | Fill request from 0x02 to 0x61 with 0xCC              |
    \*-----------------------------------------------------*/
    memset(&request[0x02], 0xCC, sizeof(request) - 2);

    /*-----------------------------------------------------*\
    | Send request and receive response packets             |
    \*-----------------------------------------------------*/
    
    ret_val &= hid_write(dev, request, 64);
    ret_val &= hid_read(dev, response, 64);

    /*-----------------------------------------------------*\
    | Extract high and low values from response             |
    \*-----------------------------------------------------*/
    unsigned char highValue = response[2] >> 4;
    unsigned char lowValue  = response[2] & 0x0F;

    /*-----------------------------------------------------*\
    | Build firmware string <high>.<low>                    |
    \*-----------------------------------------------------*/
    // char version_APROM[50];

    printf("APROM %d.%d\n", highValue, lowValue);

    /*-----------------------------------------------------*\
    | First read the LDROM                                  |
    | Checksum also available at report ID 184, with MSB    |
    | stored at index 0x08 and LSB at 0x09                  |
    \*-----------------------------------------------------*/

    /*-----------------------------------------------------*\
    | Set up LDROM Firmware Version Request packet          |
    \*-----------------------------------------------------*/
    request[0x00]   = 0x01;
    request[0x01]   = 0xB6;

    /*-----------------------------------------------------*\
    | Send request and receive response packets             |
    \*-----------------------------------------------------*/
    ret_val &= hid_write(dev, request, 64);
    ret_val &= hid_read(dev, response, 64);

    /*-----------------------------------------------------*\
    | Extract high and low values from response             |
    \*-----------------------------------------------------*/
    highValue = response[2] >> 4;
    lowValue  = response[2] & 0x0F;

    /*-----------------------------------------------------*\
    | Build firmware string <high>.<low>                    |
    \*-----------------------------------------------------*/
    // version_LDROM = std::to_string((int)highValue).append(".").append(std::to_string((int)lowValue));

    printf("LDROM %d.%d\n", highValue, lowValue);

    if (ret_val == 0) {
        fprintf(stderr, "Error getting fw version\n");
        return 0;
    }

    ///////////// get feature report ///////////////////////


    struct FeaturePacket_185 data;
    int len = hid_get_feature_report(dev, (unsigned char*)&data, sizeof(data));
    printf("recieve length %d\n", len);
    printf("size of data %ld\n", sizeof data);

    printFeaturePacket(&data);

    struct Color col;
    col.R = 20;
    col.G = 20;
    col.B = 20;

    data.j_rainbow_1.effect = MSI_MODE_STATIC;
    data.j_rainbow_1.color = col;
    data.j_rainbow_1.save_data = 1;
    // data.j_rainbow_1.color2 = col;

    int len2 = hid_send_feature_report(dev, (unsigned char*)&data, sizeof(data));
    printf("recieve length transmit %d\n", len2);


    printf("Done\n");
}