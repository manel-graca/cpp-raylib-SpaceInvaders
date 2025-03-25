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
    void TakeDamage(int dmg) override;

  private:
    bool IsRecovering() { return recoverTime < recoverTimeWhenShot; };
    float flickerDuration = 0.1f;
    float lastFlicker = 0.0f;
    float lastShot = 0.0f;
    float fireRate = 0.2f;
    float recoverTimeWhenShot = 3.0f;
    float recoverTime = 0.0f;
    float timeSinceWasHit = 0.0f;
    float minTimeToWaitBetweenHits = 0.02f;
};