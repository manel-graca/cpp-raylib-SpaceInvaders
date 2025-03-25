#include "player.hpp"
#include <iostream>
#include <raylib.h>

Player::Player()
    : Ship(1, {GetScreenWidth() / 2.0f, GetScreenHeight() - 50.0f}, 5.0f, {0, 0}, true)
{
    Image img = LoadImage("assets/graphics/tiny-spaceships/tiny_ship1.png");
    texture = LoadTextureFromImage(img);
    std::cout
        << "Player texture loaded with ID: " << texture.id << std::endl;
    UnloadImage(img);

    std::cout
        << "Player created with ID: " << id << std::endl;
}

void Player::Draw()
{
    Vector2 drawPosition = {position.x - texture.width / 2.0f, position.y - texture.height / 2.0f};
    DrawTextureEx(texture, drawPosition, 0, 1, WHITE);
}

void Player::Update()
{
    lastShot += GetFrameTime();

    HandleInput();

    position.x += direction.x * speed;
}

void Player::HandleInput()
{
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        EScreenBoundary hit = IsHittingBounds();

        if (hit == EScreenBoundary::LEFT)
        {
            direction = {0, 0};
        }
        else
        {
            direction = {-1, 0};
        }
    }
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        EScreenBoundary hit = IsHittingBounds();

        if (hit == EScreenBoundary::RIGHT)
        {
            direction = {0, 0};
        }
        else
        {
            direction = {1, 0};
        }
    }
    else
    {
        direction = {0, 0};
    }
}

void Player::Reset()
{
    position = {GetScreenWidth() / 2.0f, GetScreenHeight() - 50.0f};
}

bool Player::CanShoot()
{
    if (lastShot >= fireRate)
    {
        lastShot = 0.0f;
        return true;
    }
    return false;
}
