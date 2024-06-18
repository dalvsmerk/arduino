class Vec2d
{
public:
  short x;
  short y;

  Vec2d() : x(0), y(0)
  {
  }

  Vec2d(short sx, short sy) : x(sx), y(sy)
  {
  }

  Vec2d add(Vec2d *second)
  {
    x += second->x;
    y += second->y;
  }

  Vec2d add(short sx, short sy)
  {
    x += sx;
    y += sy;
  }
};
