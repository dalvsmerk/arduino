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
  // placeFruit();
}

void Game::placeSnake()
{
  snake.body[0].x = 4;
  snake.body[0].y = 5;

  snake.body[1].x = 4;
  snake.body[1].y = 4;

  snake.body[2].x = 4;
  snake.body[2].y = 3;

  snake.dir.x = 0;
  snake.dir.y = -1;
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
  moveSnake();

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

void Game::moveSnake()
{
  for (int i = 0; i < 64; i++)
  {
    int x = snake.body[i].x;
    int y = snake.body[i].y;

    state[x][y] = 0;
  }

  for (int i = 0; i < 64; i++)
  {
    if (snake.body[i].x == -1 || snake.body[i].y == -1)
    {
      continue;
    }

    snake.body[i].x = snake.body[i].x + snake.dir.x;
    snake.body[i].y = snake.body[i].y + snake.dir.y;

    if (snake.body[i].x < 0)
    {
      snake.body[i].x = 7;
    }

    if (snake.body[i].x == 8)
    {
      snake.body[i].x = 0;
    }

    if (snake.body[i].y < 0)
    {
      snake.body[i].y = 7;
    }

    if (snake.body[i].y == 8)
    {
      snake.body[i].y = 0;
    }

    int x = snake.body[i].x;
    int y = snake.body[i].y;

    // Serial.print("i=");
    // Serial.print(i);
    // Serial.print(";");
    // Serial.print("x=");
    // Serial.print(x);
    // Serial.print(";");
    // Serial.print("y=");
    // Serial.print(y);
    // Serial.println(";");

    state[x][y] = 1;
  }
}
