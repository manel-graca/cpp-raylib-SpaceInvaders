#include "game.hpp"
#include <raylib.h>

Game::Game()
    : player(), bulletsManager(), enemies({})
{
    Image bulletImage = LoadImage("assets/graphics/bullet1.png");
    bulletTexture = LoadTextureFromImage(bulletImage);
    UnloadImage(bulletImage);

    Enemy enemy = Enemy(2, {GetScreenWidth() / 2.0f, 50.0f}, {0, 1}, 2.0f);
    enemies.push_back(enemy);
}

Game::~Game()
{
    UnloadTexture(bulletTexture);
    for (int i = 0; i < enemies.size(); i++)
    {
        UnloadTexture(enemies[i].GetTexture());
    }
}

void Game::Draw()
{
    bulletsManager.Draw();
    player.Draw();

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].Draw();
    }
}

void Game::Update()
{
    bulletsManager.Update();
    player.Update();

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].Update();
    }

    if (IsKeyDown(KEY_SPACE))
    {
        Vector2 playerPos = player.GetPosition();
        bulletsManager.CreateBullet({playerPos.x + player.GetTexture().width / 4.0f,
                                     playerPos.y},
                                    10, WHITE, bulletTexture);
    }
}