#include "bulletsManager.hpp"

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

void BulletsManager::CreateBullet(Vector2 position, Vector2 size, float speed, Color color)
{
    if (!CanShoot())
        return;
    lastShot = 0.0f;
    bullets.push_back(Bullet(position, size, speed, color));
}

bool BulletsManager::CanShoot()
{
    return lastShot >= fireRate;
}