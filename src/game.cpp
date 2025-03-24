#include "game.hpp"
#include "bullet.hpp"
#include "obstacle.hpp"
#include <algorithm>
#include <raylib.h>
#include <raymath.h>
#include <vector>

Game::Game()
    : player(), bulletsManager(), score(0), lastEnemySpawnTime(0.0f), enemySpawnInterval(1.0f)
{
    textureManager.LoadTexture("bullet", "assets/graphics/bullet1.png");
    textureManager.LoadTexture("enemyBullet", "assets/graphics/bullet.png");
    textureManager.LoadTexture("explosion", "assets/graphics/explosion_red.png");

    constexpr int totalEnemyTextures = 19;
    for (int i = 0; i < totalEnemyTextures; i++)
    {
        std::string textureKey = "enemy" + std::to_string(i);
        std::string texturePath = "assets/graphics/tiny-spaceships/tiny_ship" + std::to_string(i) + ".png";
        textureManager.LoadTexture(textureKey, texturePath);
    }

    bulletsManager.SetEnemyBulletTexture(textureManager.GetTexture("enemyBullet"));
    enemies.push_back(std::make_unique<Enemy>(2, GetEnemySpawnPosition(), Vector2{0, 1}, 0.5f, bulletsManager, textureManager.GetTexture("enemy2")));

    CreateObstacles();
}

Game::~Game()
{
    textureManager.UnloadAllTextures();
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
            std::string textureKey = "enemy" + std::to_string(GetRandomValue(0, 18));
            enemies.push_back(std::make_unique<Enemy>(2, GetEnemySpawnPosition(), Vector2{0, 1}, 0.5f, bulletsManager, textureManager.GetTexture(textureKey)));
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
        HandleBulletCollision(enemyRect, 2.0f, [&enemy]()
                              { enemy->TakeDamage(1); });
    }

    for (auto &obstacle : obstacles)
    {
        Rectangle obstacleRect = obstacle->GetCollisionRect();
        HandleBulletCollision(obstacleRect, 1.25f, []() {});
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
                                    10, WHITE, textureManager.GetTexture("bullet"));
    }
}

Vector2 Game::GetEnemySpawnPosition()
{
    float x = GetRandomValue(0, GetScreenWidth() - 50);
    return {x, -50};
}

void Game::HandleBulletCollision(Rectangle targetRect, float explosionScale, std::function<void()> onCollision)
{
    for (auto &bullet : bulletsManager.GetBullets())
    {
        if (bullet.GetID() != 1)
            continue;

        Rectangle bulletRect = bullet.GetCollisionRect();
        if (CheckCollisionRecs(targetRect, bulletRect))
        {
            explosions.push_back(std::make_unique<ExplosionFX>(bullet.GetPosition(), explosionScale, textureManager.GetTexture("explosion")));
            bullet.SetIsAlive(false);
            onCollision();
        }
    }
}