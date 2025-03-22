#pragma once
#include "bulletsManager.hpp"
#include "ship.hpp"
#include <raylib.h>

class Enemy : public Ship
{
  public:
    Enemy(int _id, Vector2 _position, Vector2 _direction, float _speed, BulletsManager &_bulletsManager);
    void Update() override;
    void Draw() override;
    void TakeDamage(int damage);
    int GetHealth();
    bool CanShoot();

  private:
    BulletsManager &bulletsManager;
    int health;
    float lastShot;
    float fireRate;
};