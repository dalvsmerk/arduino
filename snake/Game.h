#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "Max7219Eng.h"

#define FPS 5

static const int DELAY = 1000 / FPS;

struct Pos
{
  int x;
  int y;
};

struct Snake
{
  Pos body[64];
  Pos dir;
};

class Game
{
public:
  Game(Max7219Eng *dsp);

  void init();
  void loop();
  int needNextFrame();
  void nextFrame();
  void placeSnake();
  void placeFruit();
  void clear();

private:
  Max7219Eng *dsp;
  int score;
  int lastFrameAt;
  Pos fruitPos;
  Snake snake;

  char state[8][8] = {
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
  };
};

#endif
