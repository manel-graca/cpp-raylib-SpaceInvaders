#include "obstacle.hpp"
#include <raylib.h>

Obstacle::Obstacle(int id, Vector2 position, float size)
    : id(id), position(position), size(size)
{
    Image img = LoadImage("assets/graphics/asteroid.png");
    texture = LoadTextureFromImage(img);
    UnloadImage(img);
}

Obstacle::~Obstacle()
{
    UnloadTexture(texture);
}

void Obstacle::Draw()
{
    Vector2 drawPosition = {position.x - texture.width / 2.0f, position.y - texture.height / 2.0f};
    DrawTextureEx(texture, drawPosition, 0, size, WHITE);
}

Vector2 Obstacle::GetPosition() const
{
    return position;
}

Rectangle Obstacle::GetCollisionRect()
{
    return Rectangle{position.x - (float)texture.width / 4, position.y - (float)texture.height / 2, (float)texture.width / 3, (float)texture.height / 2};
}
