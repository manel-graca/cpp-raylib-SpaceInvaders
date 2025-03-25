#pragma once
#include <raylib.h>
class Obstacle
{
  public:
    Obstacle(int id, Vector2 position, float size);
    ~Obstacle();
    void Draw();
    Vector2 GetPosition() const;

    Rectangle GetCollisionRect();

  private:
    int id;
    Vector2 position;
    float size;
    Texture2D texture;
};