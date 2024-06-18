struct Vec2d
{
  int x;
  int y;
};

class Snake
{
public:
  Snake()
  {
    dir = {
        .x = 1,
        .y = 0};

    for (int i = 0; i < 64; i++)
    {
      body[i].x = -1;
      body[i].y = -1;
    }
  }

private:
  Vec2d body[64];
  Vec2d dir;
};
