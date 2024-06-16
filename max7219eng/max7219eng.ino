#include "Max7219Eng.h"
#include "Led7x4Demo.h"

#define DIN 4
#define CLK 3
#define LOAD 2
#define DIGITS 4

Max7219Eng dsp(DIN, CLK, LOAD, DIGITS);
Led7x4Demo demo(&dsp);

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
  demo.fromOneToFour();
  delay(1000);
  dsp.blink(200);
  delay(200);
  dsp.blink(200);
  delay(200);
  dsp.blink(200);
  demo.temperature(35);
}

void loop()
{
}
