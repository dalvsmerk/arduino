#include "Vec2d.h"

class Snake
{
public:
  Snake()
  {
    for (int i = 0; i < 64; i++)
    {
      body[i] = Vec2d(-1, -1);
    }

    body[0] = Vec2d(4, 5);
    body[1] = Vec2d(4, 4);
    body[2] = Vec2d(4, 3);

    dir = Vec2d(0, -1);

    // body[0].x = 4;
    // body[0].y = 5;

    // body[1].x = 4;
    // body[1].y = 4;

    // body[2].x = 4;
    // body[2].y = 3;
  }

private:
  Vec2d body[64];
  Vec2d dir;
};
