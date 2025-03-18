#pragma once

#include <raylib.h>

class Bullet
{
  public:
    Bullet(Vector2 position, float speed, Color color, Texture2D texture);
    void Draw();
    void Update();
    bool IsAlive();

  private:
    Vector2 position;
    float speed;
    Color color;
    Texture2D texture;
    bool isAlive;
};