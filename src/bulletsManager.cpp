#include "bulletsManager.hpp"
#include <raylib.h>

BulletsManager::BulletsManager()
{
}

void BulletsManager::Draw()
{
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].Draw();
    }
}

void BulletsManager::Update()
{
    lastShot += GetFrameTime();
    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].Update();
    }
}

void BulletsManager::CreateBullet(Vector2 position, float speed, Color color, Texture2D texture)
{
    if (!CanShoot())
        return;
    lastShot = 0.0f;
    bullets.push_back(Bullet(position, speed, color, texture));
}

bool BulletsManager::CanShoot()
{
    return lastShot >= fireRate;
}