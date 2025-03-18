#pragma once
#include "ship.hpp"
#include <raylib.h>

class Player : public Ship
{
  public:
    Player(Vector2 position, float speed, Color color, std::string texturePath);
    void Update();
    void Reset();
    void HandleInput();
};