#include "player.hpp"
#include "ColorHelper.hpp"
#include <raylib.h>

Player::Player(Vector2 position, float speed, Color color)
    : Ship(position, speed, color)
{
    hue = 0.0f;
}

void Player::Draw()
{
    DrawTriangle(position, {position.x - 10, position.y + 10}, {position.x + 10, position.y + 10}, color);
}

void Player::Update()
{
    // I wanna do a trippy effect and have the color be changing all the time in the color range
    hue += hueIncrement;
    if (hue >= 360.0f)
        hue -= 360.0f;
    color = ColorHelper::HueToRGB(hue);
}

void Player::Move(Vector2 direction)
{
    position.x += direction.x * speed;
}

void Player::Reset()
{
    position = {GetScreenWidth() / 2.0f, GetScreenHeight() - 50.0f};
}

bool Player::IsHittingBounds()
{
    if (position.x < 0 || position.x > GetScreenWidth())
    {
        return true;
    }
    return false;
}

Vector2 Player::GetPosition()
{
    return position;
}

Vector2 Player::GetDirection()
{
    return direction;
}