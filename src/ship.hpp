#pragma once
#include <raylib.h>

class Ship
{
  public:
    Ship(Vector2 position, float speed, Color color);
    void Draw();
    void Update();
    void Reset();
    void Move(Vector2 direction);
    Vector2 GetPosition();
    Vector2 GetDirection();
    bool IsHittingBounds();

  protected:
    Vector2 position;
    Vector2 direction;
    float speed;
    Color color;
};