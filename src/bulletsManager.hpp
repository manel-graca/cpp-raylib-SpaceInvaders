#pragma once
#include "bullet.hpp"
#include <raylib.h>
#include <vector>

class BulletsManager
{
  public:
    BulletsManager();
    ~BulletsManager();
    void Draw();
    void Update();
    void CreateBullet(int id, Vector2 posiion, float speed, Color color, Texture2D texture);
    std::vector<Bullet> &GetBullets();
    Texture2D GetEnemyBulletTexture();
    void SetEnemyBulletTexture(Texture2D texture);

  private:
    std::vector<Bullet> bullets;
    Texture2D enemyBulletTexture;
};