#pragma once

#include <raylib.h>

class ExplosionFX
{
  public:
    ExplosionFX(Vector2 position, float scale, Texture2D texture);
    void Update();
    void Draw();
    bool IsFinished() const;

  private:
    Vector2 offset;
    Vector2 position;
    float scale;
    float currentFrame;
    float framesCounter;
    float frameSpeed;
    Texture2D texture;
    bool isFinished;
};