#pragma once
#include "bulletsManager.hpp"
#include "enemy.hpp"
#include "explosionFX.hpp"
#include "obstacle.hpp"
#include "player.hpp"
#include <memory>
#include <raylib.h>
#include <vector>

class Game
{
  public:
    void extracted();
    Game();
    ~Game();
    void Draw();
    void HandlePlayerShoot();
    void Update();
    void CreateObstacles();
    Player player;
    BulletsManager bulletsManager;
    Vector2 GetEnemySpawnPosition();

  private:
    int score;
    Texture2D bulletTexture;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Obstacle>> obstacles;
    std::vector<std::unique_ptr<ExplosionFX>> explosions;
    float lastEnemySpawnTime = 0.0f;
    float enemySpawnInterval = 1.0f;
    int maxEnemiesAlive = 8;
};
