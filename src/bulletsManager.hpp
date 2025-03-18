#pragma once
#include "bullet.hpp"
#include <raylib.h>
#include <vector>

class BulletsManager
{
  public:
    BulletsManager();
    void Draw();
    void Update();
    void CreateBullet(Vector2 posiion, float speed, Color color, Texture2D texture);

  private:
    std::vector<Bullet> bullets;
    bool CanShoot();
    float lastShot = 0.0f;
    float fireRate = 0.2f;
};