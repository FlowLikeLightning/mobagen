#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
#include <unordered_map>
using namespace std;
struct WallInfo{
  bool top, right, bottom, left;

};

bool RecursiveBacktrackerExample::Step(World* w) {
  if (stack.empty() && randomStartPoint(w) == Point2D(INT_MAX, INT_MAX)) {
    return false;
  }
  if (stack.empty()) {
    stack.push_back(randomStartPoint(w));
    return true;
  }
  Point2D current(stack.back());

  auto homies = getVisitables(w, current);
  if (homies.empty())  // visited
  {
    //breakwall?
  }
  if (homies.size() == 1)  // no random
  {
    Point2D cPoint = homies.back();
    visited[cPoint.x][cPoint.y];
  }
  if (homies.size() > 1)  // random
  {
    int randomChoice = Random::Range(0, homies.size() - 1);
    Point2D rcPoint = homies[randomChoice];
    visited[rcPoint.x][rcPoint.y];



  }

}



void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}
Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;

  std::vector<Point2D> visitables;
  if (p.y>-sideOver2&&visited[p.x][p.y-1])
  {
    visitables.push_back(p.Up());

  }

  if (p.y<sideOver2&&visited[p.x][p.y+1])
  {
    visitables.push_back(p.Down());

  }
  if (p.x>sideOver2&&visited[p.x+1][p.y])
  {
    visitables.push_back(p.Right());

  }
  if (p.x>sideOver2&&visited[p.x-1][p.y])
  {
    visitables.push_back(p.Left());
    

  }




  return visitables;
}
