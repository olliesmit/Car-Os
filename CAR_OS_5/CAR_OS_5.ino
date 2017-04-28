#include "avr/pgmspace.h"
#include <stdlib.h>    // for itoa
#include <EEPROM.h>
#include "U8glib.h"  //LCD LIB
#include "M2tk.h"    //LCD MENU
#include "utility/m2ghu8g.h" //M2tk EXT
#include "FastLED.h" //LED LIB
//#define HALF_STEP
//U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);  // I2C / TWI
//U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK); // Display which does not send ACK
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_DEV_0 | U8G_I2C_OPT_FAST); // Dev 0, Fast I2C / TWI
//U8GLIB_ST7920_128X64_4X u8g(23, 17, 16);  // Reprap LCD SPI Com: SCK = en = 23, MOSI = rw = 17, CS = di = 16


//TODO Anolouge VAR pIN in LED LOOP
//TODO Anolouge LDR pIN in LED LOOP
//Menu For LDR

const uint8_t caros_bitmap[] __attribute__((section(".progmem.data"))) =
{
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0e, 0x1c, 0x38, 0x70, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf1, 0xe3, 0xc7, 0x8f, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf1, 0xe3, 0xc7, 0x8f, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf1, 0xe3, 0xc7, 0x8f, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf1, 0xe3, 0xc7, 0x8f, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf1, 0xe3, 0xc7, 0x8f, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf1, 0xe3, 0xc7, 0x8f, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x80, 0x0f, 0xf0, 0x0f, 0x00, 0x7f, 0xe0, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0x80, 0x3f, 0xf8, 0x0f, 0x80, 0x7f, 0xf8, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0x80, 0xfc, 0x38, 0x0f, 0x80, 0x78, 0x7c, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0x80, 0xf0, 0x00, 0x1f, 0x80, 0x78, 0x3c, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0x81, 0xe0, 0x00, 0x1f, 0xc0, 0x78, 0x3c, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0x83, 0xe0, 0x00, 0x3d, 0xc0, 0x78, 0x3c, 0x30, 0x01, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x07, 0x81, 0x83, 0xc0, 0x00, 0x39, 0xe0, 0x78, 0x78, 0x48, 0xff, 0xe1, 0xf0, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x83, 0xc0, 0x00, 0x39, 0xe0, 0x78, 0xf8, 0x87, 0xff, 0xe1, 0xf0, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x83, 0xc0, 0x00, 0x78, 0xf0, 0x7f, 0xe0, 0x87, 0xff, 0xe1, 0xf0, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x83, 0xc0, 0x00, 0x70, 0xf0, 0x7f, 0xc0, 0x48, 0xff, 0xe0, 0xe0, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x83, 0xc0, 0x00, 0xf0, 0xf0, 0x7b, 0xe0, 0x30, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0x83, 0xe0, 0x00, 0xff, 0xf8, 0x79, 0xe0, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0x81, 0xe0, 0x00, 0xff, 0xf8, 0x79, 0xf0, 0x30, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0x81, 0xf0, 0x01, 0xe0, 0x7c, 0x78, 0xf8, 0x48, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x80, 0xfc, 0x19, 0xe0, 0x3c, 0x78, 0x7c, 0x87, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x80, 0x3f, 0xf9, 0xe0, 0x3c, 0x78, 0x3c, 0x87, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x80, 0x0f, 0xf3, 0xc0, 0x1e, 0x78, 0x3e, 0x48, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0x80, 0x1f, 0x80, 0x1f, 0xf0, 0x00, 0x00, 0x7f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x80, 0x7f, 0xe0, 0x7f, 0xf8, 0x00, 0x00, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x80, 0xf0, 0xf0, 0x78, 0x38, 0x00, 0x01, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x81, 0xe0, 0x78, 0xf0, 0x00, 0x00, 0x03, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x81, 0xe0, 0x78, 0xf0, 0x00, 0x00, 0x07, 0xf0, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0x83, 0xc0, 0x3c, 0xf8, 0x00, 0x00, 0x0f, 0xe0, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0x83, 0xc0, 0x3c, 0xfc, 0x00, 0x00, 0x1f, 0xc0, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0x83, 0xc0, 0x3c, 0x7f, 0x80, 0x00, 0x3f, 0x83, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x83, 0xc0, 0x3c, 0x1f, 0xf0, 0x00, 0x3f, 0x07, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x83, 0xc0, 0x3c, 0x03, 0xf8, 0x00, 0x3e, 0x0f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x83, 0xc0, 0x3c, 0x00, 0x7c, 0x00, 0x3c, 0x1f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x83, 0xc0, 0x3c, 0x00, 0x3c, 0x00, 0x3c, 0x3f, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0x81, 0xe0, 0x78, 0x00, 0x3c, 0x00, 0x3c, 0x7e, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0x81, 0xe0, 0x78, 0x00, 0x3c, 0x00, 0x3c, 0x7c, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0x80, 0xf0, 0xf0, 0xf0, 0x78, 0x00, 0x3c, 0x78, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0x80, 0x7f, 0xe0, 0xff, 0xf0, 0x00, 0x3c, 0x78, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x81, 0x80, 0x1f, 0x80, 0x3f, 0xc0, 0x00, 0x3c, 0x78, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x78, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x78, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x78, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x78, 0x00, 0x00, 0xf1, 0xe3, 0xc7, 0x8f, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x78, 0x00, 0x00, 0xf1, 0xe3, 0xc7, 0x8f, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x78, 0x00, 0x00, 0xf1, 0xe3, 0xc7, 0x8f, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x78, 0x00, 0x00, 0xf1, 0xe3, 0xc7, 0x8f, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x78, 0x00, 0x00, 0xf1, 0xe3, 0xc7, 0x8f, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x78, 0x00, 0x00, 0xf1, 0xe3, 0xc7, 0x8f, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0e, 0x1c, 0x38, 0x70, 0xff, 0xff
};

//User Defined Vars
//#define ENABLE_PULLUPS

#define maxperiod 100 // Acceleration Reset time
#define acceleration 60 // Higher = faster, (Linear)
static int pinA = 18; // Our first hardware interrupt pin is digital pin 2
static int pinB = 19; // Our second hardware interrupt pin is digital pin 3
#define endoder_select 3
/*volatile byte aFlag = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
volatile byte bFlag = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
volatile byte encoderPos = 0; //this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255
volatile byte oldEncPos = 0; //stores the last encoder position value so we can compare to the current reading and see if it has changed (so we know when to print to the serial monitor)
volatile byte reading = 0; //somewhere to store the direct values we read from our interrupt pins before checking to see if we have moved a whole detent
*/
//#define dimmer_in
//#define VaristorMIN 945
//#define VaristorMAX 1001

#define heater_pin 30
#define mfd_pin 26
#define headlighta_pin 28
#define headlightb_pin 24
#define footwell_pin 32
#define instrument_pin 22
#define heater_len 6
#define mfd_len 4
#define headlight_len 2
#define footwell_len 18
#define speedo_len 17
#define needle_len 4
#define miles_len 2

//Rotarty Encoder

uint32_t _timeLast; // last time read
// Use the full-step state table (emits a code at 00 only)
const unsigned char ttable[7][4] =
{
  {0x0, 0x2, 0x4,  0x0}, {0x3, 0x0, 0x1, 0x10},
  {0x3, 0x2, 0x0,  0x0}, {0x3, 0x2, 0x1,  0x0},
  {0x6, 0x0, 0x4,  0x0}, {0x6, 0x5, 0x0, 0x10},
  {0x6, 0x5, 0x4,  0x0},
};
volatile unsigned char state = 0;


//System Vars
const int instrument_len = speedo_len + needle_len + miles_len;
const int NUM_LEDS = heater_len + mfd_len + headlight_len + footwell_len + instrument_len;

const int heater_index = 0;
const int mfd_index = heater_len;
const int headlight_index =  heater_len + mfd_len;
const int footwell_index = heater_len + mfd_len + headlight_len;
const int speedo_index = heater_len + mfd_len + headlight_len + footwell_len;
const int needle_index = heater_len + mfd_len + headlight_len + footwell_len + speedo_len;
const int miles_index = heater_len + mfd_len + headlight_len + footwell_len + speedo_len + needle_len;

uint8_t brightness = 0;

int8_t heater_col;
int8_t mfd_col;
int8_t headlight_col;
int8_t footwell_col;
int8_t speedo_col;
int8_t needle_col;
int8_t miles_col;

CRGB leds[NUM_LEDS];
CHSV ledpreset[5]; //Preset Colours

//Brightness Compensation Mask
uint8_t power = 10;
uint8_t compensation[NUM_LEDS] = {0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0};
//=================================LCD==========================================
//Vars:

//------------------------------Declaration-------------------------------------
M2_EXTERN_ALIGN(top_el_x2l_menu);
M2_EXTERN_ALIGN(top_el_colours);
M2_EXTERN_ALIGN(top_el_compensation);
M2_EXTERN_ALIGN(top_el_brightness);
M2_ROOT(el_rb_goto_top, NULL, " top menu ", &top_el_x2l_menu);
//------------------------------X2LMENU Structure-------------------------------
char buf[20];
int8_t * set_preset;
int8_t current_preset = 1;
uint8_t index = 0;
uint8_t one_first = 0;
uint8_t one_cnt = 1;



uint8_t el_x2l_first = 0;
uint8_t el_x2l_cnt = 3;


//------------------------------Preset_Set--------------------------------------
const char *preset_set(uint8_t idx, uint8_t msg)
{
  if ( msg == M2_STRLIST_MSG_GET_STR )
  {
    switch(idx)
    {
      case 1:
        strcpy(buf, "Heater: ");
        set_preset = &heater_col;
        break;
      case 2:
        strcpy(buf, "MFD: ");
        set_preset = &mfd_col;
        break;
      case 3:
        strcpy(buf, "Dials: ");
        set_preset = &speedo_col;
        break;
      case 4:
        strcpy(buf, "Needles: ");
        set_preset = &needle_col;
        break;
      case 5:
        strcpy(buf, "Headlight: ");
        set_preset = &headlight_col;
        break;
      case 6:
        strcpy(buf, "Footwell: ");
        set_preset = &footwell_col;
        break;
      case 7:
        strcpy(buf, "Odometer: ");
        set_preset = &miles_col;
        break;
      default:
        return NULL;
    }
    if (*set_preset == 0)
    {
      strcpy(buf + strlen(buf), "Off");
    }
    else
    {
      itoa(*set_preset, buf + strlen(buf), 10);
    }
    return buf;
  }
  if ( msg == M2_STRLIST_MSG_SELECT )
  {
    switch (idx)
    {
      case 1:
        set_preset = &heater_col;
        break;
      case 2:
        set_preset = &mfd_col;
        break;
      case 3:
        set_preset = &speedo_col;
        break;
      case 4:
        set_preset = &needle_col;
        break;
      case 5:
        set_preset = &headlight_col;
        break;
      case 6:
        set_preset = &footwell_col;
        break;
      case 7:
        set_preset = &miles_col;
        break;
    }
    if (*set_preset > 3)
    {
      *set_preset = 0;
    }
    else
    {
      *set_preset = (*set_preset + 1);
    }
    Serial.println(idx);
    Serial.println(" set_preset:");
    Serial.println(*set_preset);
    Savedata();
    setleds();
    FastLED.show();
  }
  return "";
}

//---------------------------Colours Submenu------------------------------------
const char *el_colour_strlist_getstr(uint8_t idx, uint8_t msg)
{
  if (msg == M2_STRLIST_MSG_GET_STR)
  {
    switch (current_preset)
    {
      case 0:
        current_preset = 1;
        return "1";
      case 1:
        return "1";
      case 2:
        return "2";
      case 3:
        return "3";
      case 4:
        return "4";
      default:
        return "ERR";
    }
  }
  if ( msg == M2_STRLIST_MSG_SELECT )
  {
    if (current_preset < 4) current_preset++;
    else current_preset = 1;
  }
}

uint8_t uint8hcb(m2_rom_void_p element, uint8_t msg, uint8_t val)
{
  if ( msg == M2_U8_MSG_SET_VALUE )
  {
    ledpreset[current_preset].h = val;
    setleds();
    FastLED.show();
  }
  return ledpreset[current_preset].h;
}

uint8_t uint8scb(m2_rom_void_p element, uint8_t msg, uint8_t val)
{
  if ( msg == M2_U8_MSG_SET_VALUE )
  {
    ledpreset[current_preset].s = val;
    setleds();
    FastLED.show();
  }
  return ledpreset[current_preset].s;
}

uint8_t uint8vcb(m2_rom_void_p element, uint8_t msg, uint8_t val)
{
  if ( msg == M2_U8_MSG_SET_VALUE )
  {
    ledpreset[current_preset].v = val;
    setleds();
    FastLED.show();
  }
  return ledpreset[current_preset].v;
}

void fn_back(m2_el_fnarg_p fnarg)
{
  m2_SetRoot(&top_el_x2l_menu);
  Savedata();
  setleds();
  FastLED.show();
}
M2_LABEL(el_label3, NULL, "Preset:");
M2_STRLIST(el_colour_strlist, "W8", &one_first, &one_cnt , el_colour_strlist_getstr);
//M2_U8NUM(el_uint8_preset, "c1", 1, 4, &set_preset);
M2_LABEL(el_labelh, NULL, "Hue");
M2_U8NUMFN(el_uint8hcb, "c3", 0, 255, uint8hcb);
M2_LABEL(el_labels, NULL, "Sat");
M2_U8NUMFN(el_uint8scb, "c3", 0, 255, uint8scb);
M2_LABEL(el_labelv, NULL, "Lum");
M2_U8NUMFN(el_uint8vcb, "c3", 0, 255, uint8vcb);
M2_BUTTON(el_back, "f4", "Back", fn_back);

M2_LIST(list_colour_preset) =
{&el_label3, &el_colour_strlist};
M2_HLIST(el_colour_preset, NULL, list_colour_preset);

M2_LIST(list_colour_combo) =
{
  &el_labelh, &el_labels, &el_labelv,
  &el_uint8hcb, &el_uint8scb, &el_uint8vcb
};
M2_GRIDLIST(el_colour_combo_grid, "c3", list_colour_combo);

M2_LIST(list_colour_menu) =
{&el_colour_preset, &el_colour_combo_grid, &el_back};
M2_VLIST(el_colour_menu, NULL, list_colour_menu);

M2_ALIGN(top_el_colours, "-1|1W64H64", &el_colour_menu);

//---------------------------Compensation Submenu-------------------------------
uint8_t uint8index(m2_rom_void_p element, uint8_t msg, uint8_t val)
{
  if ( msg == M2_U8_MSG_SET_VALUE )
  {
    index = val;
    fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
    leds[index] = CRGB(255, 255, 255);
    FastLED.show();
  }
  if ( msg == M2_U8_MSG_GET_VALUE )
  {
    return index;
  }
}

uint8_t uint8brightness(m2_rom_void_p element, uint8_t msg, uint8_t val)
{
  if ( msg == M2_U8_MSG_SET_VALUE )
  {
    compensation[index] = val;
    setleds();
    FastLED.show();
  }
  if ( msg == M2_U8_MSG_GET_VALUE )
  {
    return compensation[index];
  }
}

void fn_reset(m2_el_fnarg_p fnarg)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    compensation[i] = 255;
  }
  Savedata();
  setleds();
  FastLED.show();
}

M2_LABEL(el_labelindex, NULL, "Index");
M2_U8NUMFN(el_uint8index, "c3", 0, NUM_LEDS - 1, uint8index);
M2_LABEL(el_labelbrightness, NULL, "Brightness");
M2_U8NUMFN(el_uint8brightness, "c3", 0, 255, uint8brightness);
M2_BUTTON(el_reset, "f4", "Reset", fn_reset);

M2_LIST(list_compensation_menu) =
{
  &el_labelindex, &el_uint8index,
  &el_labelbrightness, &el_uint8brightness,
  &el_back, &el_reset
};
M2_GRIDLIST(el_compensation_menu, "c2", list_compensation_menu);

M2_ALIGN(top_el_compensation, "-1|1W64H64", &el_compensation_menu);

//-----------------------------Brightness_Set-----------------------------------
uint8_t set_brightness(m2_rom_void_p element, uint8_t msg, uint8_t val)
{
  if ( msg == M2_U8_MSG_SET_VALUE )
  {
    power = val;
    Savedata();
    FastLED.setBrightness(power);
    setleds();
    FastLED.show();
  }
  return power;
}

//M2_LABEL(el_setbrightness, NULL, "Brightness");
M2_U8NUMFN(el_totalbrightness, "c3", 0, 255, set_brightness);

M2_LIST(list_brightness_menu) =
{
  &el_labelbrightness,
  &el_totalbrightness,
  &el_back
};
M2_VLIST(el_brightness_menu, "c2", list_brightness_menu);

M2_ALIGN(top_el_brightness, "-1|1W64H64", &el_brightness_menu);


m2_xmenu_entry xmenu_data[] =
{
  { "Set Presets", NULL, NULL },
  { ".", NULL, preset_set },
  { ".", NULL, preset_set },
  { ".", NULL, preset_set },
  { ".", NULL, preset_set },
  { ".", NULL, preset_set },
  { ".", NULL, preset_set },
  { ".", NULL, preset_set },
  { "Preset Colours", &top_el_colours, NULL },
  { "Compensation", &top_el_compensation, NULL },
  { "Brightness", &top_el_brightness, NULL },
//{ "", NULL, temp },
  {NULL, NULL, NULL},
};

// M2_X2LMENU definition
// Option l4 = four visible lines
// Option e15 = first column has a width of 15 pixel
// Option W43 = second column has a width of 43/64 of the display width
// Option F3 = select font 3 for the extra column (icons)

M2_X2LMENU(el_x2lmenu, "l4e15W43F3", &el_x2l_first, &el_x2l_cnt, xmenu_data, 65, 102, '\0');
M2_SPACE(el_x2l_space, "W1h1");
M2_VSB(el_x2l_vsb, "l4W2r1", &el_x2l_first, &el_x2l_cnt);
M2_LIST(list_x2l) = { &el_x2lmenu, &el_x2l_space, &el_x2l_vsb };
M2_HLIST(el_x2l_hlist, NULL, list_x2l);
M2_ALIGN(top_el_x2l_menu, "-1|1W64H64", &el_x2l_hlist);

//------------------------------m2 Object---------------------------------------
// Note: Use the "m2_eh_4bd" handler, which fits better to the "m2_es_arduino_rotary_encoder"
M2tk m2(&top_el_x2l_menu, m2_es_arduino_rotary_encoder, m2_eh_4bd, m2_gh_u8g_ffs);
//==============================================================================

// Arduino Setup & Loop


void setup()
{
  //Boot Image
  u8g.firstPage();
  Readdata();
  do
  {
    u8g.drawBitmapP(0, 0, 16, 128, caros_bitmap);
  }
  while( u8g.nextPage() );
  //FastLED.addLeds<TYPE, PIN, ORDER(OPTIONAL)>(ARRAYNAME, INDEX , STRIP LENGTH)
  pinMode(13, OUTPUT); //DIAG
  digitalWrite(13, LOW);
  //pinMode(pinA, INPUT_PULLUP);
  //pinMode(pinB, INPUT_PULLUP);
  //pinMode(endoder_select, INPUT_PULLUP);
  //pinMode(3, INPUT); //12V Cig Lighter

  FastLED.addLeds<WS2811, heater_pin, BRG>(leds, heater_index, heater_len);
  FastLED.addLeds<WS2811, mfd_pin, BRG>(leds, mfd_index, mfd_len);
  FastLED.addLeds<WS2811, headlighta_pin, BRG>(leds, headlight_index, 1);
  FastLED.addLeds<WS2811, headlightb_pin, BRG>(leds, headlight_index + 1, 1);
  FastLED.addLeds<WS2811, footwell_pin, BRG>(leds, footwell_index, footwell_len);
  FastLED.addLeds<WS2811, instrument_pin, BRG>(leds, speedo_index, instrument_len);
  FastLED.setBrightness(power);
  ledpreset[0].h = 0;
  ledpreset[0].s = 0;
  ledpreset[0].v = 0;
  // Connect M2tk
  m2_SetU8g(u8g.getU8g(), m2_u8g_box_icon);
  // Assign u8g font to index 0
  m2.setFont(0, u8g_font_6x13r);
  // Assign icon font to index 3
  m2.setFont(3, u8g_font_m2icon_7);
  // Define Inputs..
  m2.setPin(M2_KEY_SELECT, endoder_select);
  m2.setPin(M2_KEY_ROT_ENC_A, pinA);
  m2.setPin(M2_KEY_ROT_ENC_B, pinB);
  setleds();
  for (int i=0; i <= 255; i++){
    if (i <= power) FastLED.setBrightness(i);
    FastLED.show();
    delay(14);
  }
  digitalWrite(13, HIGH);
}

void loop()
{
  m2.checkKey();
  // process events and redraw menu if required
  if ( m2.handleKey() != 0 )
  {
    // picture loop starts here
    u8g.firstPage();
    do
    {
      // check rotary encoder also inside the picture loop
      m2.checkKey();
      // draw menu
      m2.draw();
    }
    while( u8g.nextPage() );
  }
  //TODO scale brightness (ldr)
  //FastLED.show();
}

void setleds(void)
{
  fill_solid(&leds[heater_index], heater_len, ledpreset[heater_col]);
  fill_solid(&leds[mfd_index], mfd_len, ledpreset[mfd_col]);
  fill_solid(&leds[headlight_index], headlight_len, ledpreset[headlight_col]);
  fill_solid(&leds[footwell_index], footwell_len, ledpreset[footwell_col]);
  fill_solid(&leds[speedo_index], speedo_len, ledpreset[speedo_col]);
  fill_solid(&leds[needle_index], needle_len, ledpreset[needle_col]);
  fill_solid(&leds[miles_index], miles_len, ledpreset[miles_col]);
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i].nscale8(compensation[i]);
  }
  FastLED.show();
}

void Savedata()
{
  for (int i = 1; i < 5; i++)
  {
    EEPROM.write (i * 3, ledpreset[i].h);
    EEPROM.write (i * 3 + 1, ledpreset[i].s);
    EEPROM.write (i * 3 + 2, ledpreset[i].v);
  }
  EEPROM.write (32, heater_col);
  EEPROM.write (33, mfd_col);
  EEPROM.write (34, headlight_col);
  EEPROM.write (35, footwell_col);
  EEPROM.write (36, speedo_col);
  EEPROM.write (37, needle_col);
  EEPROM.write (38, miles_col);
  EEPROM.write (40, power);
  for (int i = 0; i < (NUM_LEDS ); i++)
  {
    EEPROM.write (i + 50, compensation[i]);
  }
  
}

void Readdata()
{
  for (int i = 1; i < 5; i++)
  {
    ledpreset[i].h = EEPROM.read(i * 3);
    ledpreset[i].s = EEPROM.read(i * 3 + 1);
    ledpreset[i].v = EEPROM.read(i * 3 + 2);
  }
  heater_col = EEPROM.read(32);
  mfd_col = EEPROM.read(33);
  headlight_col = EEPROM.read(34);
  footwell_col = EEPROM.read(35);
  speedo_col = EEPROM.read(36);
  needle_col = EEPROM.read(37);
  miles_col = EEPROM.read(38);
  power = EEPROM.read(40);
  for (int i = 0; i < (NUM_LEDS); i++)
  {
    compensation[i] = EEPROM.read(i + 50);
  }
}



