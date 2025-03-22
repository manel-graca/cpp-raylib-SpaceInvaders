#include "game.hpp"
#include "obstacle.hpp"
#include <algorithm>
#include <raylib.h>

Game::Game()
    : player(), bulletsManager()
{
    Image bulletImage = LoadImage("assets/graphics/bullet1.png");
    bulletTexture = LoadTextureFromImage(bulletImage);
    UnloadImage(bulletImage);

    enemies.push_back(std::make_unique<Enemy>(2, Vector2{GetScreenWidth() / 2.0f, 50.0f}, Vector2{0, 1}, 0.5f));

    for (int i = 0; i < 3; i++)
    {
        float x = (GetScreenWidth() - 375) / 2.0f + i * 145;
        float y = GetScreenHeight() - 250;

        obstacles.push_back(std::make_unique<Obstacle>(i, Vector2{x, y}, 1.0f));
    }
}

Game::~Game()
{
    UnloadTexture(bulletTexture);
    for (int i = 0; i < enemies.size(); i++)
    {
        UnloadTexture(enemies[i]->GetTexture());
    }
}

void Game::Draw()
{
    bulletsManager.Draw();
    player.Draw();

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->Draw();
    }

    for (int i = 0; i < obstacles.size(); i++)
    {
        obstacles[i]->Draw();
    }
}

void Game::Update()
{
    bulletsManager.Update();
    player.Update();

    for (auto &enemy : enemies)
    {
        Rectangle enemyRect = enemy->GetRectangleRect();
        for (auto &bullet : bulletsManager.GetBullets())
        {
            Rectangle bulletRect = {bullet.GetPosition().x, bullet.GetPosition().y, (float)bullet.GetTexture().width, (float)bullet.GetTexture().height};
            if (CheckCollisionRecs(enemyRect, bulletRect))
            {
                enemy->TakeDamage(1);
                bullet.SetIsAlive(false);
            }
        }
    }

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                                 [](const std::unique_ptr<Enemy> &enemy)
                                 { return !enemy->IsAlive(); }),
                  enemies.end());

    bulletsManager.GetBullets().erase(std::remove_if(bulletsManager.GetBullets().begin(), bulletsManager.GetBullets().end(),
                                                     [](const Bullet &bullet)
                                                     { return !bullet.IsAlive(); }),
                                      bulletsManager.GetBullets().end());

    Rectangle playerRect = player.GetRectangleRect();
    for (auto &enemy : enemies)
    {
        if (CheckCollisionRecs(playerRect, enemy->GetRectangleRect()))
        {
            // player.TakeDamage(1); // Assuming player has a TakeDamage() method
        }
    }

    for (auto &obstacle : obstacles)
    {
        Rectangle obstacleRect = obstacle->GetCollisionRect();
        for (auto &bullet : bulletsManager.GetBullets())
        {
            Rectangle bulletRect = {bullet.GetPosition().x, bullet.GetPosition().y, (float)bullet.GetTexture().width, (float)bullet.GetTexture().height};
            if (CheckCollisionRecs(obstacleRect, bulletRect))
            {
                bullet.SetIsAlive(false);
            }
        }
    }

    for (auto &obstacle : obstacles)
    {
        if (CheckCollisionRecs(playerRect, obstacle->GetCollisionRect()))
        {
            // player.TakeDamage(1); // Assuming player has a TakeDamage() method
        }
    }

    for (auto &enemy : enemies)
    {
        enemy->Update();
    }

    if (IsKeyDown(KEY_SPACE))
    {
        Vector2 playerPos = player.GetPosition();
        bulletsManager.CreateBullet({playerPos.x + player.GetTexture().width / 4.0f,
                                     playerPos.y},
                                    10, WHITE, bulletTexture);
    }
}