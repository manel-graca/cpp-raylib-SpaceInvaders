#include "game.hpp"
#include "bullet.hpp"
#include "obstacle.hpp"
#include <algorithm>
#include <raylib.h>
#include <vector>

Game::Game()
    : player(), bulletsManager(), score(0), lastEnemySpawnTime(0.0f), enemySpawnInterval(1.0f)
{
    Image bulletImage = LoadImage("assets/graphics/bullet1.png");
    bulletTexture = LoadTextureFromImage(bulletImage);
    UnloadImage(bulletImage);

    enemies.push_back(std::make_unique<Enemy>(2, GetEnemySpawnPosition(), Vector2{0, 1}, 0.5f, bulletsManager));

    CreateObstacles();
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

    for (int i = 0; i < explosions.size(); i++)
    {
        explosions[i]->Draw();
    }
}

void Game::Update()
{
    bulletsManager.Update();
    player.Update();

    std::vector<Bullet> &bullets = bulletsManager.GetBullets();

    lastEnemySpawnTime += GetFrameTime();

    if (enemies.size() < maxEnemiesAlive)
    {
        if (lastEnemySpawnTime >= enemySpawnInterval)
        {
            lastEnemySpawnTime = 0.0f;
            enemies.push_back(std::make_unique<Enemy>(2, GetEnemySpawnPosition(), Vector2{0, 1}, 0.5f, bulletsManager));
        }
    }

    HandlePlayerShoot();

    for (auto &enemy : enemies)
    {
        enemy->Update();
    }

    for (auto &enemy : enemies)
    {
        Rectangle enemyRect = enemy->GetRectangleRect();
        for (auto &bullet : bulletsManager.GetBullets())
        {
            if (bullet.GetID() != 1)
                continue;

            Rectangle bulletRect = {bullet.GetPosition().x, bullet.GetPosition().y, (float)bullet.GetTexture().width, (float)bullet.GetTexture().height};
            if (CheckCollisionRecs(enemyRect, bulletRect))
            {
                explosions.push_back(std::make_unique<ExplosionFX>(enemy->GetPosition(), 2.0f));
                enemy->TakeDamage(1);
                bullet.SetIsAlive(false);
            }
        }
    }

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                                 [](const std::unique_ptr<Enemy> &enemy)
                                 { return !enemy->IsAlive(); }),
                  enemies.end());

    for (auto it = bullets.begin(); it != bullets.end();)
    {
        if (!it->IsAlive())
        {
            it = bullets.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for (int i = explosions.size() - 1; i >= 0; i--)
    {
        explosions[i]->Update();
        if (explosions[i]->IsFinished())
        {
            explosions.erase(explosions.begin() + i); // Remove finished explosion
        }
        else
        {
            explosions[i]->Draw();
        }
    }
}

void Game::CreateObstacles()
{
    for (int i = 0; i < 3; i++)
    {
        float x = (GetScreenWidth() - 375) / 2.0f + i * 145;
        float y = GetScreenHeight() - 250;

        obstacles.push_back(std::make_unique<Obstacle>(i, Vector2{x, y}, 1.0f));
    }
}

void Game::HandlePlayerShoot()
{
    if (!player.CanShoot())
        return;

    if (IsKeyDown(KEY_SPACE))
    {
        Vector2 playerPos = player.GetPosition();
        bulletsManager.CreateBullet(1, {playerPos.x + player.GetTexture().width / 4.0f, playerPos.y},
                                    10, WHITE, bulletTexture);
    }
}

Vector2 Game::GetEnemySpawnPosition()
{
    float x = GetRandomValue(0, GetScreenWidth() - 50);
    return {x, -50};
}