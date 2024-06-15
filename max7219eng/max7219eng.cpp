#include "max7219eng.h"

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

// DEMO

void Max7219Eng::fromOneToFour()
{
  setDecodeMode(DecodeMode::decodeD0D3());
  transfer(D0, 0x01);
  transfer(D1, 0x02);
  transfer(D2, 0x03);
  transfer(D3, 0x04);
}

void Max7219Eng::zeros()
{
  setDecodeMode(DecodeMode::decodeD0D3());
  transfer(D0, 0x00);
  transfer(D1, 0x00);
  transfer(D2, 0x00);
  transfer(D3, 0x00);
}

/**
 * @param degreesC Will clamp to [0; 99] if out of range
 */
void Max7219Eng::temperature(u8 degreesC)
{
  if (degreesC > 99)
  {
    degreesC = 99;
  }

  u8 first = (degreesC - degreesC % 10) / 10;
  u8 second = degreesC % 10;

  setDecodeMode(DecodeMode::noDecode());
  transfer(D0, DIGITS[first]);
  transfer(D1, DIGITS[second]);
  transfer(D2, 0b01100011);
  transfer(D3, 0b01001110);
}

void Max7219Eng::blink(int delayMs)
{
  transfer(SHUTDOWN, 0);
  delay(delayMs);
  transfer(SHUTDOWN, 1);
  delay(delayMs);
  transfer(SHUTDOWN, 0);
  delay(delayMs);
  transfer(SHUTDOWN, 1);
  delay(delayMs);
  transfer(SHUTDOWN, 0);
  delay(delayMs);
  transfer(SHUTDOWN, 1);
}

void Max7219Eng::transfer(u8 addr, u8 data)
{
  // LOAD has to be LOW the whole time during transmission
  digitalWrite(pinLoad, LOW);

  // Why this doesn't work?
  // u16 packet = addr << 8 | data;
  // shiftOut(pinDin, pinClk, MSBFIRST, packet);

  // But this works:
  shiftOut(pinDin, pinClk, MSBFIRST, addr);
  shiftOut(pinDin, pinClk, MSBFIRST, data);

  // Latch 16-bit DIN from shift register on LOAD rise
  digitalWrite(pinLoad, HIGH);
  digitalWrite(pinLoad, LOW);
}
