#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "Max7219Eng.h"

#define FPS 5

static const int DELAY = 1000 / FPS;

struct Vec2d
{
  int x;
  int y;
};

struct Snake
{
  Vec2d body[64];
  Vec2d dir;
};

class Game
{
public:
  Game(Max7219Eng *dsp);

  void init();
  int needNextFrame();
  void nextFrame();

private:
  Max7219Eng *dsp;
  int score;
  int lastFrameAt;
  Vec2d fruitPos;
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

  void placeSnake();
  void placeFruit();
  void clear();

  void moveSnake();
};

#endif
