#include "ship.hpp"
#include <iostream>
#include <raylib.h>

Ship::Ship(Vector2 position, float speed, Color color, std::string texturePath)
{
    this->position = position;
    this->speed = speed;
    this->color = color;
    this->direction = {0, 0};
    this->isAlive = true;

    Image image = LoadImage(texturePath.c_str());
    texture = LoadTextureFromImage(image);
    UnloadImage(image);

    std::cout << "Ship created! Position: " << position.x << ", " << position.y << std::endl;
}

Ship::~Ship()
{
    if (texture.id != 0)
        UnloadTexture(texture);
}

void Ship::Draw()
{
    if (texture.id != 0)
        DrawTexture(texture, position.x, position.y, color);
    else
        DrawRectangle(position.x, position.y, 50, 50, color);
}

void Ship::Update()
{
    position.x += direction.x * speed;
    position.y += direction.y * speed;
}

void Ship::SetAlive(bool alive)
{
    isAlive = alive;
}

Texture2D Ship::GetTexture()
{
    return texture;
}

void Ship::SetDirection(Vector2 direction)
{
    this->direction = direction;
}

Vector2 Ship::GetPosition()
{
    return position;
}

Vector2 Ship::GetDirection()
{
    return direction;
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