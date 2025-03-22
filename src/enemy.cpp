#include "enemy.hpp"
#include <string>

Enemy::Enemy(int _id, Vector2 _position, Vector2 _direction, float _speed)
    : Ship(_id, _position, _speed, _direction, true)
{
    std::string filePath = "assets/graphics/tiny-spaceships/tiny_ship" + std::to_string(id) + ".png";
    Image img = LoadImage(filePath.c_str());
    texture = LoadTextureFromImage(img);
    UnloadImage(img);
}

void Enemy::Update()
{
    position.x += direction.x * speed;
    position.y += direction.y * speed;
}

void Enemy::Draw()
{
    DrawTexture(texture, position.x, position.y, WHITE);
}

void Enemy::TakeDamage(int damage)
{
    health -= damage;

    if (health <= 0)
    {
        SetIsAlive(false);
    }
}
