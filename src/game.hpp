#pragma once
#include "bulletsManager.hpp"
#include "enemiesManager.hpp"
#include "player.hpp"
#include <raylib.h>

class Game
{
  public:
    Game();
    ~Game();
    void Draw();
    void Update();
    BulletsManager bulletsManager;
    EnemiesManager enemiesManager;
    Player player;

  private:
    int score;
    Texture2D bulletTexture;
};
