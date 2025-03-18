#include "game.hpp"
#include <raylib.h>

Game::Game()
    : player(), bulletsManager()
{
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
    player.Draw();
}

void Game::Update()
{
    bulletsManager.Update();
    player.Update();

    if (IsKeyDown(KEY_SPACE))
    {
        Vector2 playerPos = player.GetPosition();
        bulletsManager.CreateBullet({playerPos.x + player.GetTexture().width / 4.0f,
                                     playerPos.y},
                                    10, WHITE, bulletTexture);
    }
}