#include "Max7219Eng.h"
#include "Game.h"

#define DIN 4
#define CLK 3
#define LOAD 2
#define DIGITS 8

const u8 diagonal[8] = {
    0b10000000,
    0b01000000,
    0b00100000,
    0b00010000,
    0b00001000,
    0b00000100,
    0b00000010,
    0b00000001};

const u8 smiley[8] = {
    0b00000000,
    0b01000010,
    0b00000000,
    0b00011000,
    0b10000001,
    0b01000010,
    0b00111100,
    0b00000000};

const u8 heart[8] = {
    0b00000000,
    0b01100110,
    0b11111111,
    0b11111111,
    0b11111111,
    0b01111110,
    0b00111100,
    0b00011000,
};

Max7219Eng dsp(DIN, CLK, LOAD, DIGITS);
Game game(&dsp);

void setup()
{
  Serial.begin(9600);
  pinMode(DIN, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(LOAD, OUTPUT);

  dsp.init();
  dsp.setIntensity(100);
  dsp.setDecodeMode(DecodeMode::noDecode());
  // dsp.test(1);
  // delay(100);
  // dsp.test(0);
  displayImage(diagonal);
  clear();

  game.init();
}

void loop()
{
  if (game.needNextFrame())
  {
    game.nextFrame();
  }
}

void demo()
{
  delay(1000);
  displayImage(diagonal);
  delay(1000);
  displayImage(smiley);
  delay(1000);
  displayImage(heart);
}

void displayImage(const u8 bitmap[8])
{
  for (short i = 0; i < 8; i++)
  {
    dsp.setDigit(i + 1, bitmap[i]);
  }
}

void clear()
{
  for (short i = 0; i < 8; i++)
  {
    dsp.setDigit(i + 1, 0);
  }
}
