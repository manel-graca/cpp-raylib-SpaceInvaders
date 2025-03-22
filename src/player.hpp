#pragma once
#include "ship.hpp"
#include <raylib.h>

class Player : public Ship
{
  public:
    Player();
    void Update() override;
    void Draw() override;
    void Reset();
    void HandleInput();
    bool CanShoot();

  private:
    float lastShot = 0.0f;
    float fireRate = 0.2f;
};