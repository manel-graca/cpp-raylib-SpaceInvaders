#include "player.hpp"
#include <raylib.h>

Player::Player(Vector2 position, float speed, Color color)
    : Ship(position, speed, color)
{
}

void Player::Draw()
{
    DrawTriangle(position, {position.x - 10, position.y + 10}, {position.x + 10, position.y + 10}, color);
}

void Player::Update()
{
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