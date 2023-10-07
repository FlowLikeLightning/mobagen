#include "JohnConway.h"

// Reference: https://playgameoflife.com/info
void JohnConway::Step(World& world) {
  for (int y = 0; y < world.SideSize(); ++y) {
    for (int x = 0; x < world.SideSize(); ++x)
    {
      int neighbors = CountNeighbors(world,Point2D(x,y));
      if ((neighbors==2&&world.Get(Point2D(x,y)))||neighbors==3)
      {
        world.SetNext(Point2D(x,y), true);
      }
      else
      {
        world.SetNext(Point2D(x,y), false);
      }
    }
  }

  world.SwapBuffers();
}

int JohnConway::CountNeighbors(World& world, Point2D point)
{
  return world.Get(point.Up())+world.Get(point.Up().Left())+world.Get(point.Up().Right())+world.Get(point.Left())+world.Get(point.Right())+world.Get(point.Down())+world.Get(point.Down().Left())+world.Get(point.Down().Right());
}
