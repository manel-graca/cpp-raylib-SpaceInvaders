#include "bulletsManager.hpp"
#include <iostream>
#include <raylib.h>

BulletsManager::BulletsManager()
{
    Image bulletImage = LoadImage("assets/graphics/bullet.png");
    enemyBulletTexture = LoadTextureFromImage(bulletImage);
    UnloadImage(bulletImage);
}

BulletsManager::~BulletsManager()
{
    UnloadTexture(enemyBulletTexture);
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

void BulletsManager::CreateBullet(int id, Vector2 position, float speed, Color color, Texture2D texture)
{
    bullets.push_back(Bullet(id, position, speed, color, texture));
}

std::vector<Bullet> &BulletsManager::GetBullets()
{
    return bullets; // Return a reference to the original vector
}

Texture2D BulletsManager::GetEnemyBulletTexture()
{
    return enemyBulletTexture;
}