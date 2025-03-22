#include "game.hpp"
#include <raylib.h>

Game::Game()
    : player(), bulletsManager(), enemies({})
{
    Image bulletImage = LoadImage("assets/graphics/bullet1.png");
    bulletTexture = LoadTextureFromImage(bulletImage);
    UnloadImage(bulletImage);

    // 2, {GetScreenWidth() / 2.0f, 50.0f}, {0, 1}, 2.0f
    enemies.push_back(std::make_unique<Enemy>(2, Vector2{GetScreenWidth() / 2.0f, 50.0f}, Vector2{0, 1}, 2.0f));

    for (int i = 0; i < 3; i++)
    {
        float x = GetScreenWidth() / 2.0f - 100.0f + i * 25;
        float y = GetScreenHeight() - 100;
        obstacles.push_back(std::make_unique<Obstacle>(i, Vector2{x, y}, 0.1f));
    }
}

Game::~Game()
{
    UnloadTexture(bulletTexture);
    for (int i = 0; i < enemies.size(); i++)
    {
        UnloadTexture(enemies[i]->GetTexture());
    }
}

void Game::Draw()
{
    bulletsManager.Draw();
    player.Draw();

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->Draw();
    }

    for (int i = 0; i < obstacles.size(); i++)
    {
        obstacles[i]->Draw();
    }
}

void Game::Update()
{
    bulletsManager.Update();
    player.Update();

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->Update();
    }

    if (IsKeyDown(KEY_SPACE))
    {
        Vector2 playerPos = player.GetPosition();
        bulletsManager.CreateBullet({playerPos.x + player.GetTexture().width / 4.0f,
                                     playerPos.y},
                                    10, WHITE, bulletTexture);
    }
}