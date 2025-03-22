#include "bulletsManager.hpp"
#include <iostream>
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

    for (auto it = bullets.begin(); it != bullets.end();)
    {
        if (!it->IsAlive())
        {
            it = bullets.erase(it); // Erase returns the next iterator
            std::cout << "Bullet erased" << std::endl;
        }
        else
        {
            ++it; // Move to the next element
        }
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

std::vector<Bullet> &BulletsManager::GetBullets()
{
    return bullets; // Return a reference to the original vector
}