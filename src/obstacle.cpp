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
    if (texture.id != 0)
        DrawTextureEx(texture, position, 0, size, WHITE);
    else
        DrawRectangle(position.x, position.y, size, size, WHITE);
}