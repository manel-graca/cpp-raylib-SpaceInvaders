#include "player.hpp"
#include "ColorHelper.hpp"
#include "ship.hpp"
#include <raylib.h>

Player::Player(Vector2 position, float speed, Color color, std::string texturePath)
    : Ship(position, speed, color, texturePath)
{
}

void Player::Update()
{
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
            SetDirection({0, 0});
        }
        else
        {
            SetDirection({-1, 0});
        }
    }
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        EScreenBoundary hit = IsHittingBounds();

        if (hit == EScreenBoundary::RIGHT)
        {
            SetDirection({0, 0});
        }
        else
        {
            SetDirection({1, 0});
        }
    }
    else
    {
        SetDirection({0, 0});
    }
}

void Player::Reset()
{
    position = {GetScreenWidth() / 2.0f, GetScreenHeight() - 50.0f};
}
