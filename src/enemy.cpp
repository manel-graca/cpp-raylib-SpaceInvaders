#include "enemy.hpp"

Enemy::Enemy(int _id, Vector2 _position, Vector2 _direction, float _speed, BulletsManager &_bulletsManager, Texture2D _texture)
    : Ship(_id, _position, _speed, _direction, true), bulletsManager(_bulletsManager), health(1), fireRate(1.0f), lastShot(0.0f)
{
    texture = _texture; // Use preloaded texture
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
