#include "game.hpp"
#include <raylib.h>

Game::Game()
    : player(Player({GetScreenWidth() / 2.0f, GetScreenHeight() - 50.0f}, 5, WHITE, "assets/graphics/tiny-spaceships/tiny_ship1.png"))
{
    bulletsManager = BulletsManager();
    enemiesManager = EnemiesManager();

    Image bulletImage = LoadImage("assets/graphics/bullet1.png");
    bulletTexture = LoadTextureFromImage(bulletImage);
    UnloadImage(bulletImage);
}

Game::~Game()
{
    UnloadTexture(bulletTexture);
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

    if (IsKeyDown(KEY_SPACE))
    {
        Vector2 playerPos = player.GetPosition();
        bulletsManager.CreateBullet({playerPos.x + player.GetTexture().width / 4,
                                     playerPos.y},
                                    10, WHITE, bulletTexture);
    }
}