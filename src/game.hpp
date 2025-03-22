#pragma once
#include "bulletsManager.hpp"
#include "enemy.hpp"
#include "obstacle.hpp"
#include "player.hpp"
#include <memory>
#include <raylib.h>
#include <vector>

class Game
{
  public:
    Game();
    ~Game();
    void Draw();
    void Update();
    Player player;
    BulletsManager bulletsManager;

  private:
    int score;
    Texture2D bulletTexture;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Obstacle>> obstacles;
};
