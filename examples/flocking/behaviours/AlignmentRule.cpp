#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2f AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to match the heading of neighbors = Average velocity
  Vector2f averageVelocity = boid->getVelocity();

  // todo: add your code here to align each boid in a neighborhood
  // hint: iterate over the neighborhood

  for (unsigned int i = 0; i < neighborhood.size(); i++)
  {
    averageVelocity+=neighborhood[i]->getVelocity();
  }
  averageVelocity/neighborhood.size();

  return Vector2f::normalized(averageVelocity);
}