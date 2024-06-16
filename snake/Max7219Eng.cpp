#include "Max7219Eng.h"

Max7219Eng::Max7219Eng(int pinDin, int pinClk, int pinLoad, short digits) : pinDin(pinDin),
                                                                            pinClk(pinClk),
                                                                            pinLoad(pinLoad),
                                                                            digits(digits)
{
  if (digits > 8)
  {
    digits = 8;
  }
}

void Max7219Eng::init()
{
  digitalWrite(pinLoad, LOW);

  transfer(SHUTDOWN, 0);
  transfer(SCAN, digits - 1);
  transfer(DECODE, 0x0F);
  transfer(SHUTDOWN, 1);
}

void Max7219Eng::shutdown(u8 enable)
{
  transfer(SHUTDOWN, enable ? 0 : 1);
}

void Max7219Eng::test(u8 enable)
{
  transfer(TEST, enable);
}

void Max7219Eng::setDecodeMode(DecodeModeEnum mode)
{
  transfer(SHUTDOWN, 0);
  transfer(DECODE, mode);
  transfer(SHUTDOWN, 1);
}

/**
 * @param percent Will clamp to [0; 100] if outside of the range
 */
void Max7219Eng::setIntensity(u8 percent)
{
  if (percent > 100)
  {
    percent = 100;
  }

  u8 intensity = map(percent, 0, 100, 0, 15);

  transfer(SHUTDOWN, 0);
  transfer(INTENSITY, intensity);
  transfer(SHUTDOWN, 1);
}

/**
 * @param digit [1; 8]
 * @param data Use Code B if using any decode mode,
 *             see "Table 5. Code B Font" from MAX7219ENG datasheet
 */
void Max7219Eng::setDigit(u8 digit, u8 data)
{
  transfer(digit, data);
}

void Max7219Eng::blink(int delayMs)
{
  transfer(SHUTDOWN, 0);
  delay(delayMs);
  transfer(SHUTDOWN, 1);
}

void Max7219Eng::transfer(u8 addr, u8 data)
{
  // LOAD has to be LOW the whole time during transmission
  digitalWrite(pinLoad, LOW);

  // Q: Why this doesn't work?
  // A: shiftOut shifts 8 bits only
  // u16 packet = addr << 8 | data;
  // shiftOut(pinDin, pinClk, MSBFIRST, packet);

  shiftOut(pinDin, pinClk, MSBFIRST, addr);
  shiftOut(pinDin, pinClk, MSBFIRST, data);

  // Latch 16-bit DIN from shift register on LOAD rise
  digitalWrite(pinLoad, HIGH);
  digitalWrite(pinLoad, LOW);
}
