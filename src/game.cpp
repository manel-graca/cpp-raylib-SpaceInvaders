#include "game.hpp"
#include "bullet.hpp"
#include "obstacle.hpp"
#include <algorithm>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <vector>

Game::Game()
    : player(), bulletsManager(), score(0), lastEnemySpawnTime(0.0f), enemySpawnInterval(2.0f), isPlaying(false)
{
    textureManager.LoadTexture("bullet", "assets/graphics/bullet1.png");
    textureManager.LoadTexture("enemyBullet", "assets/graphics/bullet.png");
    textureManager.LoadTexture("explosion", "assets/graphics/explosion_red.png");
    textureManager.LoadTexture("obstacle", "assets/graphics/asteroid.png");
    textureManager.LoadTexture("player", "assets/graphics/tiny-spaceships/tiny_ship1.png");

    constexpr int totalEnemyTextures = 19;
    for (int i = 0; i < totalEnemyTextures; i++)
    {
        std::string textureKey = "enemy" + std::to_string(i);
        std::string texturePath = "assets/graphics/tiny-spaceships/tiny_ship" + std::to_string(i) + ".png";
        textureManager.LoadTexture(textureKey, texturePath);
    }

    bulletsManager.SetEnemyBulletTexture(textureManager.GetTexture("enemyBullet"));

    CreateObstacles();
}

Game::~Game()
{
    textureManager.UnloadAllTextures();
}

void Game::Draw()
{
    if (!IsPlaying())
        return;

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
    if (!IsPlaying())
        return;

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
                                 [this](const std::unique_ptr<Enemy> &enemy)
                                 {
                                     if (!enemy->IsAlive())
                                     {
                                         AddScore(1);
                                         return true;
                                     }
                                     return false;
                                 }),
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
    Texture2D texture = textureManager.GetTexture("obstacle");
    float screenWidth = (float)(GetScreenWidth());
    float screenHeight = (float)(GetScreenHeight());
    float obstacleWidth = (float)(texture.width);
    float spacing = 50.0f;
    int obstacleCount = 3;

    float totalWidth = obstacleCount * obstacleWidth + (obstacleCount - 1) * spacing;
    float groupStartX = (screenWidth - totalWidth) / 2.0f;
    float y = screenHeight / 2.0f + 175;

    for (int i = 0; i < obstacleCount; ++i)
    {
        float x = groupStartX + i * (obstacleWidth + spacing) + obstacleWidth / 2.0f;
        obstacles.push_back(std::make_unique<Obstacle>(2, Vector2{x, y}, 1.0f));
    }
}

void Game::HandlePlayerShoot()
{
    if (!player.CanShoot())
        return;

    if (IsKeyDown(KEY_SPACE))
    {
        Vector2 playerPos = player.GetPosition();
        bulletsManager.CreateBullet(1, {playerPos.x - player.GetTexture().width / 4.0f, playerPos.y - 5},
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
        {
            Rectangle bulletRect = bullet.GetCollisionRect();
            Rectangle playerRect = player.GetRectangleRect();
            if (CheckCollisionRecs(playerRect, bulletRect))
            {
                explosions.push_back(std::make_unique<ExplosionFX>(bullet.GetPosition(), explosionScale, textureManager.GetTexture("explosion")));
                bullet.SetIsAlive(false);
                player.TakeDamage(1);
                if (!player.IsAlive())
                {
                    ResetGame();
                    return;
                }
            }

            continue;
        }

        Rectangle bulletRect = bullet.GetCollisionRect();
        if (CheckCollisionRecs(targetRect, bulletRect))
        {
            explosions.push_back(std::make_unique<ExplosionFX>(bullet.GetPosition(), explosionScale, textureManager.GetTexture("explosion")));
            bullet.SetIsAlive(false);
            onCollision();
        }
    }
}

void Game::ResetGame()
{
    player.Reset();
    bulletsManager.Reset();
    enemies.clear();
    explosions.clear();
    score = 0;
    lastEnemySpawnTime = 0.0f;
    isPlaying = false;
}

void Game::AddScore(int value)
{
    score += value;
    std::cout << "Score: " << score << std::endl;
}