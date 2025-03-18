#include "bullet.hpp"
#include <raylib.h>

Bullet::Bullet(Vector2 position, float speed, Color color, Texture2D texture)
{
    this->position = position;
    this->speed = speed;
    this->color = color;
    this->texture = texture;
}

void Bullet::Draw()
{
    DrawTexture(texture, position.x, position.y, color);
}

void Bullet::Update()
{
    position.y -= speed;
}