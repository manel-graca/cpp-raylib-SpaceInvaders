#pragma once

#include <raylib.h>

class Bullet
{
  public:
    Bullet(Vector2 position, Vector2 size, float speed, Color color);
    void Draw();
    void Update();

  private:
    Vector2 position;
    Vector2 size;
    float speed;
    Color color;
};