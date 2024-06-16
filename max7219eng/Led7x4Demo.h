#ifndef LED7X4DEMO_H
#define LED7X4DEMO_H

#include <Arduino.h>
#include "Max7219Eng.h"

class Led7x4Demo
{
public:
  Led7x4Demo(Max7219Eng *dsp) : dsp(dsp) {}

  void fromOneToFour()
  {
    dsp->setDecodeMode(DecodeMode::decodeD0D3());
    dsp->setDigit(D0, 0x01);
    dsp->setDigit(D1, 0x02);
    dsp->setDigit(D2, 0x03);
    dsp->setDigit(D3, 0x04);
  }

  void zeros()
  {
    dsp->setDecodeMode(DecodeMode::decodeD0D3());
    dsp->setDigit(D0, 0x00);
    dsp->setDigit(D1, 0x00);
    dsp->setDigit(D2, 0x00);
    dsp->setDigit(D3, 0x00);
  }

  /**
   * @param degreesC Will clamp to [0; 99] if out of range
   */
  void temperature(u8 degreesC)
  {
    if (degreesC > 99)
    {
      degreesC = 99;
    }

    u8 first = (degreesC - degreesC % 10) / 10;
    u8 second = degreesC % 10;

    dsp->setDecodeMode(DecodeMode::noDecode());
    dsp->setDigit(D0, DIGITS[first]);
    dsp->setDigit(D1, DIGITS[second]);
    dsp->setDigit(D2, 0b01100011);
    dsp->setDigit(D3, 0b01001110);
  }

private:
  Max7219Eng *dsp;
};

#endif
