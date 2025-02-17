/*
This goes below
switch (keycode) {
        case FN_MO13:

*/
uint8_t packet[32];

 void get_qmk_version(void) //Grab the QMK Version
{
        packet[0] = id_signalrgb_qmk_version;
        packet[1] = QMK_VERSION_BYTE_1;
        packet[2] = QMK_VERSION_BYTE_2;
        packet[3] = QMK_VERSION_BYTE_3;

        raw_hid_send(packet, 32);
}

void get_signalrgb_protocol_version(void) //Grab what version of the SignalRGB protocol a keyboard is running
{
        packet[0] = id_signalrgb_protocol_version;
        packet[1] = PROTOCOL_VERSION_BYTE_1;
        packet[2] = PROTOCOL_VERSION_BYTE_2;
        packet[3] = PROTOCOL_VERSION_BYTE_3;

        raw_hid_send(packet, 32);
}

void get_unique_identifier(void) //Grab the unique identifier for each specific model of keyboard.
{
        packet[0] = id_signalrgb_unique_identifier;
        packet[1] = DEVICE_UNIQUE_IDENTIFIER_BYTE_1;
        packet[2] = DEVICE_UNIQUE_IDENTIFIER_BYTE_2;
        packet[3] = DEVICE_UNIQUE_IDENTIFIER_BYTE_3;

        raw_hid_send(packet, 32);
}

void led_streaming(uint8_t *data) //Stream data from HID Packets to Keyboard.
{
    uint8_t index = data[1];
    uint8_t numberofleds = data[2]; 

    if(numberofleds >= 10)
    {
        packet[1] = DEVICE_ERROR_LEDS;
        raw_hid_send(packet,32);
        return; 
    } 
    
    for (uint8_t i = 0; i < numberofleds; i++)
    {
      uint8_t offset = (i * 3) + 3;
      uint8_t  r = data[offset];
      uint8_t  g = data[offset + 1];
      uint8_t  b = data[offset + 2];
    
      rgb_matrix_set_color(index + i, r, g, b);
     }
}

void signalrgb_mode_enable(void)
{
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SIGNALRGB); //Set RGB Matrix to SignalRGB Compatible Mode
}

void signalrgb_mode_disable(void)
{
    rgb_matrix_reload_from_eeprom(); //Reloading last effect from eeprom
}

void signalrgb_total_leds(void)//Grab total number of leds that a board has.
{
    packet[0] = id_signalrgb_total_leds;
    packet[1] = RGB_MATRIX_LED_COUNT;
    raw_hid_send(packet,32);
}

void signalrgb_firmware_type(void) //Grab which fork of qmk a board is running.
{
    packet[0] = id_signalrgb_firmware_type;
    packet[1] = FIRMWARE_TYPE_BYTE;
    raw_hid_send(packet,32);
}


/*
Part of void raw_hid_receive(uint8_t *data, uint8_t length) {
specifically in (*command_id)
right before protocol version

*/
        
        case id_signalrgb_qmk_version:
        {
            get_qmk_version();
            break;
        }

        case id_signalrgb_protocol_version:
        {
            get_signalrgb_protocol_version();
            break;
        }

        case id_signalrgb_unique_identifier:
        {
            get_unique_identifier();
            break;
        }

        case id_signalrgb_stream_leds: 
        {
            led_streaming(data);
            break;
        }

        case id_signalrgb_effect_enable: 
        {
            signalrgb_mode_enable();
            break;
        }

        case id_signalrgb_effect_disable: 
        {
            signalrgb_mode_disable();
            break;
        }

        case id_signalrgb_total_leds:
        {
            signalrgb_total_leds();
            break;
        }

        case id_signalrgb_firmware_type:
        {
            signalrgb_firmware_type();
            break;
        }
