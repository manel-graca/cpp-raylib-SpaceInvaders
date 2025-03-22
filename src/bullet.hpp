#pragma once

#include <raylib.h>

class Bullet
{
  public:
    Bullet(Vector2 position, float speed, Color color, Texture2D texture);
    void Draw();
    void Update();
    bool IsAlive() const { return isAlive; }
    void SetIsAlive(bool isAlive);
    Vector2 GetPosition() const { return position; }
    Rectangle GetCollisionRect() const { return {position.x, position.y, (float)texture.width, (float)texture.height}; }
    Texture2D GetTexture() const { return texture; }

  private:
    Vector2 position;
    float speed;
    Color color;
    Texture2D texture;
    bool isAlive;
};