#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"
#include "engine/Engine.h"

Vector2f SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  // Try to avoid boids too close
  Vector2f separatingForce = Vector2f::zero();


  float desiredDistance = desiredMinimalDistance;
  //
  //    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them

  if (!neighborhood.empty())
  {
    Vector2f position = boid->transform.position;
    int countCloseFlockmates = 0;
    for (int i = 0; i < neighborhood.size(); ++i)
    {

      auto diff = position-neighborhood[i]->getPosition();
      if (diff.getMagnitude()<=desiredDistance)
      {
        countCloseFlockmates++;
        separatingForce+=(Vector2f(1,1)/diff)/diff.getMagnitude();
        separatingForce = Vector2f::normalized(separatingForce);
        boid->applyForce(separatingForce);
      }

    }
    //separatingForce = Vector2f::normalized(separatingForce);


    // todo: find and apply force only on the closest mates
  }




  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  ImGui::SetCurrentContext(world->engine->window->imGuiContext);
  bool valusHasChanged = false;

  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valusHasChanged = true;
  }

  return valusHasChanged;
}
