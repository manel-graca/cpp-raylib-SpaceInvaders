#pragma once
#include "bulletsManager.hpp"
#include "enemy.hpp"
#include "player.hpp"
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
    std::vector<Enemy> enemies;
};
