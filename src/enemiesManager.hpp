#pragma once
#include "ship.hpp"
#include <raylib.h>
#include <vector>

class EnemiesManager
{
  public:
    EnemiesManager();
    void Draw();
    void Update();
    void CreateEnemy(Vector2 position, float speed, Color color, std::string texturePath);

  private:
    std::vector<Ship> enemies;
    int startEnemyCount = 20;
};
