#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce = Vector2f::zero();

  // todo: add your code here to make a force towards the center of mass
  Vector2f centerMass;
  for (unsigned int i = 0; i < neighborhood.size(); i++)
  {
    if (neighborhood[i]==boid){i++;}

    centerMass+=neighborhood[i]->getPosition();
  }
  centerMass-=boid->getPosition();
  centerMass/=neighborhood.size()-1;

  if(cohesionForce.getMagnitude()<=boid->getDetectionRadius())
  {
    cohesionForce = centerMass - boid->getPosition();
  }
  if(cohesionForce.getMagnitude()>boid->getDetectionRadius())
  {
    cohesionForce = Vector2f(0,0);

  }

  // hint: iterate over the neighborhood
  // find center of mass



  return cohesionForce.normalized();
}