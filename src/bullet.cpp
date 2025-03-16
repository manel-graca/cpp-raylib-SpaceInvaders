#include "bullet.hpp"

Bullet::Bullet(Vector2 position, Vector2 size, float speed, Color color)
{
    this->position = position;
    this->size = size;
    this->speed = speed;
    this->color = color;
}

void Bullet::Draw()
{
    DrawRectangleV(position, size, color);
}

void Bullet::Update()
{
    position.y -= speed;
}