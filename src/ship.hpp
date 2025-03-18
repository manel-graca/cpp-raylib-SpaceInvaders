#pragma once
#include "enums.hpp"
#include <raylib.h>

class Ship
{
  public:
    Ship(int _id, Vector2 _position, float _speed, Vector2 _direction, bool _isAlive);
    ~Ship();
    int GetID();
    Vector2 GetPosition();
    Vector2 GetDirection();
    float GetSpeed();
    bool IsAlive();
    Texture2D GetTexture();
    EScreenBoundary IsHittingBounds();
    EScreenBoundary IsOutsideBounds();
    virtual void SetIsAlive(bool isAlive);
    virtual void Update();
    virtual void Draw();

  protected:
    int id;
    float speed;
    Vector2 position;
    Vector2 direction;
    bool isAlive;
    Texture2D texture;
};