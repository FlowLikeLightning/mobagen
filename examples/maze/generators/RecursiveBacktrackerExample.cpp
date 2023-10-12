#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
#include <unordered_map>
using namespace std;
struct WallInfo{
  bool top, right, bottom, left;
};
void raptureWall(World* w, Point2D beginning, Point2D objective)
{

  auto sideOver2 = w->GetSize() / 2;
  auto diff = objective - beginning;
  if (diff.y <=-1&& objective.y >= -sideOver2)
  {
    w->SetNorth(objective.Down(), false);

  }
  if(diff.y>=1 && objective.y <= sideOver2)
  {
    w->SetSouth(objective.Up(), false);

  }
  if(diff.x>=1 && objective.x <= sideOver2)
  {
    w->SetEast(objective.Left(), false);
  }
  if (diff.x<=-1&& objective.x>=-sideOver2)
  {
    w->SetWest(objective.Right(),false);
  }

}
bool RecursiveBacktrackerExample::Step(World* w) {
  auto randomStart = randomStartPoint(w);
  // bootstrap for stopping
  if (stack.empty() && randomStart == Point2D(INT_MAX, INT_MAX))
    return false;

  // bootstrap for starting
  if (stack.empty()) {
    stack.push_back(randomStart);
    return true;
  }

  Point2D current(stack.back());
  visited[current.x][current.y] = true;
  w->SetNodeColor(current,Color::Red);

  auto homies = getVisitables(w, current);
  if (homies.empty())  // visited
  {
    w->SetNodeColor(current,Color::Black);
    stack.pop_back();
    return true;
  }
  if (homies.size() == 1)  // no random
  {
    Point2D cPoint = homies.back();
    w->SetNodeColor(cPoint,Color::Green);

    stack.push_back(cPoint);
    raptureWall(w,current,cPoint);

    visited[cPoint.x][cPoint.y] = true;
  }
  if (homies.size() > 1)  // random aka the problem
  {
    int randomChoice = Random::Range(0, homies.size()-1);
    Point2D rcPoint = homies[randomChoice];
    w->SetNodeColor(rcPoint,Color::Green);
    raptureWall(w,current,rcPoint);

    visited[rcPoint.x][rcPoint.y] = true;
    stack.push_back(rcPoint);
  }
  return true;
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
  if (p.y>-sideOver2&&!visited[p.x][p.y-1])
    visitables.push_back(p.Up());
  if (p.y<sideOver2&&!visited[p.x][p.y+1])
    visitables.push_back(p.Down());
  if (p.x<sideOver2&&!visited[p.x+1][p.y])
    visitables.push_back(p.Right());
  if (p.x>-sideOver2&&!visited[p.x-1][p.y])
    visitables.push_back(p.Left());

  return visitables;
}