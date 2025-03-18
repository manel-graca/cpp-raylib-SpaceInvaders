#include "ship.hpp"
#include <raylib.h>

Ship::Ship(int _id, Vector2 _position, float _speed, Vector2 _direction, bool _isAlive)
{
    id = _id;
    position = _position;
    speed = _speed;
    direction = _direction;
    isAlive = _isAlive;
}

Ship::~Ship()
{
    if (texture.id != 0)
        UnloadTexture(texture);
}

Vector2 Ship::GetPosition()
{
    return position;
}

Vector2 Ship::GetDirection()
{
    return direction;
}

float Ship::GetSpeed()
{
    return speed;
}

void Ship::SetIsAlive(bool isAlive)
{
    this->isAlive = isAlive;
}

bool Ship::IsAlive()
{
    return isAlive;
}

Texture2D Ship::GetTexture()
{
    return texture;
}

EScreenBoundary Ship::IsHittingBounds()
{
    if (position.y < 0)
    {
        return EScreenBoundary::TOP;
    }
    if (position.y > GetScreenHeight())
    {
        return EScreenBoundary::BOTTOM;
    }
    if (position.x < 0)
    {
        return EScreenBoundary::LEFT;
    }
    if (position.x + texture.width > GetScreenWidth())
    {
        return EScreenBoundary::RIGHT;
    }
    return EScreenBoundary::NONE;
}

EScreenBoundary Ship::IsOutsideBounds()
{
    if (position.y - texture.height < 0)
    {
        return EScreenBoundary::TOP;
    }
    if (position.y + texture.height > GetScreenHeight())
    {
        return EScreenBoundary::BOTTOM;
    }
    if (position.x - texture.width < 0)
    {
        return EScreenBoundary::LEFT;
    }
    if (position.x + texture.width > GetScreenWidth())
    {
        return EScreenBoundary::RIGHT;
    }
    return EScreenBoundary::NONE;
}

void Ship::Update()
{
}

void Ship::Draw()
{
}