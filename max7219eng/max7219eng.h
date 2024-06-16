#ifndef MAX7219ENG_H
#define MAX7219ENG_H

#include <Arduino.h>

#define u16 unsigned short
#define u8 unsigned char

enum RegisterEnum
{
  NO_OP = 0x0,
  D0 = 0x1,
  D1 = 0x2,
  D2 = 0x3,
  D3 = 0x4,
  D4 = 0x5,
  D5 = 0x6,
  D6 = 0x7,
  D7 = 0x8,
  DECODE = 0x9,
  INTENSITY = 0xA,
  SCAN = 0xB,
  SHUTDOWN = 0xC,
  TEST = 0xF
};

enum DecodeModeEnum
{
  NO_DECODE = 0x0,
  DECODE_D0 = 0x1,
  DECODE_D0_D3 = 0xF,
  DECODE_D0_D7 = 0xFF
};

class DecodeMode
{
public:
  static DecodeModeEnum noDecode() { return NO_DECODE; }
  static DecodeModeEnum decodeD0() { return DECODE_D0; }
  static DecodeModeEnum decodeD0D3() { return DECODE_D0_D3; }
  static DecodeModeEnum decodeD0D7() { return DECODE_D0_D7; }
};

static const u8 DIGITS[10] = {
    0b01111110, // 0
    0b00110000, // 1
    0b01101101, // 2
    0b01111001, // 3
    0b00110010, // 4
    0b01011011, // 5
    0b01011111, // 6
    0b01110000, // 7
    0b01111111, // 8
    0b01111011, // 9
};

/**
 * @example
```cpp
#include "max7219eng.h"

#define DIN 4
#define CLK 3
#define LOAD 2
#define DIGITS 4

Max7219Eng dsp(DIN, CLK, LOAD, DIGITS);

void setup()
{
  pinMode(DIN, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(LOAD, OUTPUT);

  dsp.init();
  dsp.setIntensity(100);
  dsp.setDigit(D0, 0b01111110);
}

void loop()
{
}
```
*/
class Max7219Eng
{
public:
  Max7219Eng(int pinDin, int pinClk, int pinLoad, short digits);

  void init();
  void setDecodeMode(DecodeModeEnum mode);
  void setIntensity(u8 percent);
  void setDigit(u8 digit, u8 data);
  void blink(int delayMs);

private:
  int pinDin;
  int pinClk;
  int pinLoad;
  short digits;

  void transfer(u8 addr, u8 data);
};

#endif
