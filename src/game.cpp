#include "game.hpp"

Game::Game()
    : player({GetScreenWidth() / 2.0f, GetScreenHeight() - 50.0f}, 5, BLUE)
{
    bulletsManager = BulletsManager();
    enemiesManager = EnemiesManager();
}

void Game::Draw()
{
    bulletsManager.Draw();
    enemiesManager.Draw();
    player.Draw();
}

void Game::Update()
{
    bulletsManager.Update();
    enemiesManager.Update();
    player.Update();

    if (IsKeyDown(KEY_LEFT))
    {
        player.Move({-1, 0});
        if (player.IsHittingBounds())
        {
            player.Move({1, 0});
        }
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        player.Move({1, 0});
        if (player.IsHittingBounds())
        {
            player.Move({-1, 0});
        }
    }
    if (IsKeyDown(KEY_SPACE))
    {
        bulletsManager.CreateBullet(player.GetPosition(), {10, 10}, 10, player.GetColor());
    }
}