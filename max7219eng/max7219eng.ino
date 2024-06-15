#include "max7219eng.h"

#define DIN 4
#define CLK 3
#define LOAD 2
#define DIGITS 4

Max7219Eng dsp(DIN, CLK, LOAD, DIGITS);

void setup()
{
  Serial.begin(9600);
  Serial.println("hello");

  pinMode(DIN, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(LOAD, OUTPUT);

  dsp.init();
  dsp.setIntensity(100);

  // DEMO
  dsp.fromOneToFour();
  delay(1000);
  dsp.blink(200);
  dsp.temperature(35);
}

void loop()
{
}
