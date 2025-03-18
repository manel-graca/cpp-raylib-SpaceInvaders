#pragma once

#include <raylib.h>

class Bullet
{
  public:
    Bullet(Vector2 position, float speed, Color color, Texture2D texture);
    void Draw();
    void Update();

  private:
    Vector2 position;
    float speed;
    Color color;
    Texture2D texture;
};