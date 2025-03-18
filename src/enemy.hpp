#pragma once
#include "ship.hpp"
#include <raylib.h>

class Enemy : public Ship
{
  public:
    Enemy(int _id, Vector2 _position, Vector2 _direction, float _speed);
    void Update() override;
    void Draw() override;

  private:
};