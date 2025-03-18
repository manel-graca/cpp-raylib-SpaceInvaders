#pragma once
#include "bulletsManager.hpp"
#include "player.hpp"
#include <raylib.h>

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
};
