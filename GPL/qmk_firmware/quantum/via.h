/* 
Part of enum via_command_id {
*/
enum via_command_id {
    id_signalrgb_qmk_version                = 0x21,
    id_signalrgb_protocol_version           = 0x22,
    id_signalrgb_unique_identifier          = 0x23,
    id_signalrgb_stream_leds                = 0x24,
    id_signalrgb_effect_enable              = 0x25,
    id_signalrgb_effect_disable             = 0x26,
    id_signalrgb_total_leds                 = 0x27,
    id_signalrgb_firmware_type              = 0x28,
    id_unhandled                            = 0xFF,
};

/* This follows directly after via_command_id */

enum signalrgb_responses {
    PROTOCOL_VERSION_BYTE_1 = 1,
    PROTOCOL_VERSION_BYTE_2 = 0,
    PROTOCOL_VERSION_BYTE_3 = 4,
    QMK_VERSION_BYTE_1 = 0,
    QMK_VERSION_BYTE_2 = 19,
    QMK_VERSION_BYTE_3 = 12,
    DEVICE_UNIQUE_IDENTIFIER_BYTE_1 = 0,
    DEVICE_UNIQUE_IDENTIFIER_BYTE_2 = 0,
    DEVICE_UNIQUE_IDENTIFIER_BYTE_3 = 0,
    FIRMWARE_TYPE_BYTE = 2, 
    DEVICE_ERROR_LEDS = 254,
};

//Changelogs for Firmware Versions------------------------------------
//V1.0.1 added detection for the total number of LEDs a board has. Plugins need a rewrite to make use of this change. Rewritten plugins will not function with older firmware.
//V1.0.2 added another detection byte for which fork of SignalRGB firmware device is running. This means we can keep overlap Unique Identifiers between Sonix and Mainline.
//V1.0.3 unifies the command IDs between Mainline, Sonix, and VIA. All commands have a 0x20 offset now.
//V1.0.4 improves detection handling, and has a complete rewrite of the plugins. Also merges Mainline and VIA branches. VIA Branch is deprecated.

/*
DEVICE, DEVICE_UNIQUE_IDENTIFIER_BYTE_1,DEVICE_UNIQUE_IDENTIFIER_BYTE_2,DEVICE_UNIQUE_IDENTIFIER_BYTE_3
gmmk/pro/rev2/ansi                0 0 5
gmmk/pro/rev2/iso                 0 0 6
gmmk/gmmk2/p65/ansi               0 0 7
gmmk/gmmk2/p65/iso                0 0 8
gmmk/gmmk2/p96/ansi               0 0 9
gmmk/gmmk2/p96/iso                0 0 10
*/


/*

This is placed directory after:
// Used by VIA to store and retrieve the layout options.

*/

//Used to handle SignalRGB Compatibility

void get_qmk_version(void);
void get_signalrgb_protocol_version(void);
void get_unique_identifier(void);
void led_streaming(uint8_t *data);
void signalrgb_mode_enable(void);
void signalrgb_mode_disable(void);
void signalrgb_total_leds(void);
void signalrgb_firmware_type(void);