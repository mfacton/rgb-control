#include <stdint.h>

#define VENDOR 0x1462
#define PRODUCT 0x7c95

#define MSI_USB_PID_COMMON  0x0076

#define NUMOF_PER_LED_MODE_LEDS     240

#define SYNC_SETTING_ONBOARD        0x01
#define SYNC_SETTING_JRAINBOW1      0x02
#define SYNC_SETTING_JRAINBOW2      0x04
#define SYNC_SETTING_JCORSAIR       0x08
#define SYNC_SETTING_JPIPE1         0x10
#define SYNC_SETTING_JPIPE2         0x20
#define SYNC_SETTING_JRGB           0x80

#define BITSET(val, bit, pos)       ((unsigned char)std::bitset<8>(val).set((pos), (bit)).to_ulong())

#define SYNC_PER_LED_MODE_JRAINBOW_LED_COUNT     40
#define SYNC_PER_LED_MODE_CORSAIR_LED_COUNT     120
#define JRAINBOW1_MAX_LED_COUNT                 200
#define JRAINBOW2_MAX_LED_COUNT                 240
#define JCORSAIR_MAX_LED_COUNT                  240

#define MSI_DIRECT_MODE                         0x25
#define PER_LED_BASIC_SYNC_MODE                 (0x80 | SYNC_SETTING_ONBOARD | SYNC_SETTING_JPIPE1 | SYNC_SETTING_JPIPE2)
#define PER_LED_FULL_SYNC_MODE                  (PER_LED_BASIC_SYNC_MODE | SYNC_SETTING_JRAINBOW1 | SYNC_SETTING_JRAINBOW2 | SYNC_SETTING_JCORSAIR)

enum Mode {
    ModeDisable                 = 0,
    ModeStatic                  = 1,
    ModeBreathing               = 2,
    ModeFlashing                = 3,
    ModeDoubleFlashing          = 4,
    ModeLightning               = 5,
    ModeMsiMarquee              = 6,
    ModeMeteor                  = 7,
    ModeWaterDrop               = 8,
    ModeMsiRainbow              = 9,
    ModePop                     = 10,
    ModeRap                     = 11,
    ModeJazz                    = 12,
    ModePlay                    = 13,
    ModeMovie                   = 14,
    ModeColorRing               = 15,
    ModePlanetary               = 16,
    ModeDoubleMeteor            = 17,
    ModeEnergy                  = 18,
    ModeBlink                   = 19,
    ModeClock                   = 20,
    ModeColorPulse              = 21,
    ModeColorShift              = 22,
    ModeColorWave               = 23,
    ModeMarquee                 = 24,
    ModeRainbow                 = 25,
    ModeRainbowWave             = 26,
    ModeVisor                   = 27,
    ModeJRainbow                = 28,
    ModeRainbowFlashing         = 29,
    ModeRainbowDoubleFlashing   = 30,
    ModeRandom                  = 31,
    ModeFanControl              = 32,
    ModeDisable2                = 33,
    ModeColorRingFlashing       = 34,
    ModeColorRingDoubleFlashing = 35,
    ModeStack                   = 36,
    ModeCorsairQue              = 37,
    ModeFire                    = 38,
    ModeLava                    = 39,
    ModeDirectDummy             = 100
};

enum Speed {
    SpeedLow    = 0,
    SpeedMedium = 1,
    SpeedHigh   = 2,
};

enum FanType {
    FanTypeSP = 0,
    FanTypeHD = 1,
    FanTypeLL = 2,
};

enum Brightness
{
    BrightnessOff = 0,
    Brightness10  = 1,
    Brightness20  = 2,
    Brightness30  = 3,
    Brightness40  = 4,
    Brightness50  = 5,
    Brightness60  = 6,
    Brightness70  = 7,
    Brightness80  = 8,
    Brightness90  = 9,
    Brightness100 = 10,
};

struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct CorsairZoneData
{
    uint8_t effect;
    struct Color color1;
    uint8_t fan_flags;
    uint8_t corsair_quantity;
    uint8_t padding[4];
    uint8_t is_individual;
};

struct ZoneData {
    uint8_t effect;
    struct Color color1;
    uint8_t speedAndBrightnessFlags;
    struct Color color2;
    uint8_t colorFlags;
    uint8_t padding;
};

struct RainbowZoneData {
    uint8_t effect;
    struct Color color1;
    uint8_t speedAndBrightnessFlags;
    struct Color color2;
    uint8_t colorFlags;
    uint8_t padding;
    uint8_t cycle_or_led_num;
};

struct FeaturePacket_185 {
    uint8_t report_id;    //0x52
    struct ZoneData            j_rgb_1;                 // 1
    struct ZoneData            j_pipe_1;                // 11
    struct ZoneData            j_pipe_2;                // 21
    struct RainbowZoneData     j_rainbow_1;             // 31
    struct RainbowZoneData     j_rainbow_2;             // 42
    struct CorsairZoneData     j_corsair;               // 53
    struct ZoneData            j_corsair_outerll120;    // 64
    struct ZoneData            on_board_led;            // 74
    struct ZoneData            on_board_led_1;          // 84
    struct ZoneData            on_board_led_2;          // 94
    struct ZoneData            on_board_led_3;          // 104
    struct ZoneData            on_board_led_4;          // 114
    struct ZoneData            on_board_led_5;          // 124
    struct ZoneData            on_board_led_6;          // 134
    struct ZoneData            on_board_led_7;          // 144
    struct ZoneData            on_board_led_8;          // 154
    struct ZoneData            on_board_led_9;          // 164
    struct ZoneData            j_rgb_2;                 // 174
    uint8_t save_data;                                  // 184
};

struct FeaturePacket_PerLED_185
{
    uint8_t report_id;
    uint8_t hdr0;
    uint8_t hdr1;
    uint8_t hdr2;
    uint8_t hdr3;
    struct Color         leds[NUMOF_PER_LED_MODE_LEDS];
};
