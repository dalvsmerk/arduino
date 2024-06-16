#include "Game.h"

Game::Game(Max7219Eng *dsp) : dsp(dsp), score(0)
{
  lastFrameAt = millis();
  fruitPos.x = -1;
  fruitPos.y = -1;

  for (int i = 0; i < 64; i++)
  {
    snake.body[i].x = -1;
    snake.body[i].y = -1;
  }
}

void Game::init()
{
  placeSnake();
  placeFruit();
}

void Game::loop()
{
}

void Game::placeSnake()
{
  snake.body[0].x = 3;
  snake.body[0].y = 4;

  snake.body[1].x = 4;
  snake.body[1].y = 4;

  snake.dir.x = -1;
  snake.dir.y = 0;

  state[4][3] = 1;
  state[4][4] = 1;
}

void Game::placeFruit()
{
  long col = random(0, 8);
  long row = random(0, 8);

  // dsp->setDigit(row, 1 << col);
  state[row][col] = 1;
  fruitPos.x = col;
  fruitPos.y = row;
  // Serial.print("x = ");
  // Serial.print(fruitPos.x);
  // Serial.print("; y = ");
  // Serial.println(fruitPos.y);
}

int Game::needNextFrame()
{
  int now = millis();

  return lastFrameAt + DELAY < now;
}

void Game::nextFrame()
{
  // Serial.println("next frame");
  clear();

  for (int i = 0; i < 8; i++)
  {
    char rowState = 0;

    for (int j = 0; j < 8; j++)
    {
      rowState |= state[i][j] << j;
    }

    dsp->setDigit(i + 1, rowState);
  }

  lastFrameAt = millis();
}

void Game::clear()
{
  for (short i = 0; i < 8; i++)
  {
    dsp->setDigit(i + 1, 0);
  }
}
