#pragma once
#include "bulletsManager.hpp"
#include "ship.hpp"
#include <raylib.h>

class Enemy : public Ship
{
  public:
    Enemy(int _id, Vector2 _position, Vector2 _direction, float _speed, BulletsManager &_bulletsManager, Texture2D _texture);
    void Update() override;
    void Draw() override;
    bool CanShoot();

  private:
    BulletsManager &bulletsManager;
    float lastShot;
    float fireRate;
};