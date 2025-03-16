#pragma once
#include "ship.hpp"
#include <raylib.h>

class Player : public Ship
{
  public:
    Player(Vector2 position, float speed, Color color);
    void Draw();
    void Update();
    void Reset();
    void Move(Vector2 direction);
    Vector2 GetPosition();
    Vector2 GetDirection();
    bool IsHittingBounds();
    Color GetColor() { return color; };

  private:
    float hue;
    const float hueIncrement = 2.0f;
};