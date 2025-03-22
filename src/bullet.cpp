#include "bullet.hpp"
#include <raylib.h>

Bullet::Bullet(int id, Vector2 position, float speed, Color color, Texture2D texture)
{
    this->id = id;
    this->position = position;
    this->speed = speed;
    this->color = color;
    this->texture = texture;
    isAlive = true;
}

void Bullet::Draw()
{
    if (!isAlive)
        return;
    DrawTexture(texture, position.x, position.y, color);
}

void Bullet::Update()
{
    if (id == 1)
        position.y -= speed;
    else
        position.y += speed;
    if (position.y < 0 || position.y > GetScreenHeight())
    {
        isAlive = false;
    }
}

void Bullet::SetIsAlive(bool isAlive)
{
    this->isAlive = isAlive;
}
