#include "enemiesManager.hpp"
#include <iostream>
#include <raylib.h>

EnemiesManager::EnemiesManager()
{
    int xPosIncrement = 5;
    int yPosIncrement = 5;
    int textureAmount = 19;
    int textureIndex = 2;

    for (int i = 0; i < startEnemyCount; i++)
    {
        // 'textureIndex' is used to select the texture for the enemy
        // it needs to be between 1 and 'textureAmount'
        if (textureIndex > textureAmount + 1)
        {
            textureIndex = 2;
        }

        std::string texturePath = "assets/graphics/tiny-spaceships/tiny_ship" + std::to_string(textureIndex) + ".png";
        std::cout << "Texture path: " << texturePath << std::endl;

        /* Vector2 position = {(float)(i * xPosIncrement), GetScreenHeight() - 50.0f + i * -yPosIncrement};
        CreateEnemy(position, 0, WHITE, texturePath);

        std::cout << "Enemy created at: " << position.x << ", " << position.y << "with index:" << i << std::endl; */
        textureIndex++;
    }
}

void EnemiesManager::Draw()
{
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].Draw();
    }
}

void EnemiesManager::Update()
{
    for (int i = 0; i < enemies.size(); i++)
    {
        Ship ship = enemies[i];
        ship.Update();
    }
}

void EnemiesManager::CreateEnemy(Vector2 position, float speed, Color color, std::string texturePath)
{
    Ship eInstance = Ship(position, speed, color, texturePath);
    enemies.push_back(eInstance);
}