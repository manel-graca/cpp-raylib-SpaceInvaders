#pragma once
#include "enums.hpp"
#include <raylib.h>
#include <string>

class Ship
{
  public:
    Ship(Vector2 position, float speed, Color color, std::string texturePath);
    ~Ship();
    void Draw();
    void Update();
    void SetDirection(Vector2 direction);
    Vector2 GetPosition();
    Vector2 GetDirection();
    bool IsAlive();
    void SetAlive(bool alive);
    EScreenBoundary IsHittingBounds();
    Texture2D GetTexture();

  protected:
    bool isAlive;
    Vector2 position;
    Vector2 direction;
    float speed;
    Color color;
    Texture2D texture;
};