#include "player.hpp"
#include <iostream>
#include <raylib.h>

Player::Player()
    : Ship(1, {GetScreenWidth() / 2.0f, GetScreenHeight() - 50.0f}, 5.0f, {0, 0}, true)
{
    recoverTime = recoverTimeWhenShot;

    Image img = LoadImage("assets/graphics/tiny-spaceships/tiny_ship1.png");
    texture = LoadTextureFromImage(img);
    std::cout
        << "Player texture loaded with ID: " << texture.id << std::endl;
    UnloadImage(img);

    std::cout
        << "Player created with ID: " << id << std::endl;
}

void Player::Draw()
{
    Color color = IsRecovering() ? RED : WHITE;

    if (IsRecovering())
    {
        color.a = (int)(lastFlicker / flickerDuration) % 2 == 0 ? 0 : 255;
    }

    Vector2 drawPosition = {position.x - texture.width / 2.0f, position.y - texture.height / 2.0f};
    DrawTextureEx(texture, drawPosition, 0, 1, color);
}

void Player::Update()
{
    lastShot += GetFrameTime();
    recoverTime += GetFrameTime();
    timeSinceWasHit += GetFrameTime();
    lastFlicker += GetFrameTime();

    HandleInput();

    position.x += direction.x * speed;
}

void Player::HandleInput()
{
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        EScreenBoundary hit = IsHittingBounds();

        if (hit == EScreenBoundary::LEFT)
        {
            direction = {0, 0};
        }
        else
        {
            direction = {-1, 0};
        }
    }
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        EScreenBoundary hit = IsHittingBounds();

        if (hit == EScreenBoundary::RIGHT)
        {
            direction = {0, 0};
        }
        else
        {
            direction = {1, 0};
        }
    }
    else
    {
        direction = {0, 0};
    }
}

void Player::Reset()
{
    position = {GetScreenWidth() / 2.0f, GetScreenHeight() - 50.0f};
}

bool Player::CanShoot()
{
    if (lastShot >= fireRate)
    {
        lastShot = 0.0f;
        return true;
    }
    return false;
}

void Player::TakeDamage(int dmg)
{
    if (timeSinceWasHit <= minTimeToWaitBetweenHits)
        return;
    timeSinceWasHit = 0.0f;

    if (recoverTime < recoverTimeWhenShot)
    {
        SetIsAlive(false);
        std::cout << "Player dies. The recover time is: " << recoverTimeWhenShot - recoverTime << " seconds" << std::endl;
    }
    else
    {
        recoverTime = 0.0f;
        lastFlicker = 0.0f;
        std::cout << "Player got hit. If hit again before " << recoverTimeWhenShot << " seconds, player should die" << std::endl;
    }
}
