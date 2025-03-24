#include "enemy.hpp"
#include <string>

Enemy::Enemy(int _id, Vector2 _position, Vector2 _direction, float _speed, BulletsManager &_bulletsManager)
    : Ship(_id, _position, _speed, _direction, true), bulletsManager(_bulletsManager), health(1), fireRate(1.0f), lastShot(0.0f)
{
    std::string filePath = "assets/graphics/tiny-spaceships/tiny_ship" + std::to_string(id) + ".png";
    Image img = LoadImage(filePath.c_str());
    texture = LoadTextureFromImage(img);
    UnloadImage(img);
}

void Enemy::Update()
{
    if (CanShoot())
    {
        bulletsManager.CreateBullet(id, Vector2{position.x + texture.width / 4.0f, position.y}, 4.0f, WHITE, bulletsManager.GetEnemyBulletTexture());
    }

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

int Enemy::GetHealth()
{
    return health;
}

bool Enemy::CanShoot()
{
    lastShot += GetFrameTime();
    if (lastShot >= fireRate)
    {
        lastShot = 0.0f;
        return true;
    }
    return false;
}
