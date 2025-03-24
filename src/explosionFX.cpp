#include "explosionFX.hpp"
#include <raylib.h>

ExplosionFX::ExplosionFX(Vector2 position, float scale, Texture2D texture)
{
    this->position = position;
    this->scale = scale;
    this->currentFrame = 0;
    this->framesCounter = 0.0f;
    this->frameSpeed = 30.0f; // (frames per second)
    this->texture = texture;
    this->isFinished = false;
    this->offset = {15, 15};
}

void ExplosionFX::Update()
{
    framesCounter += GetFrameTime();
    if (framesCounter >= 1.0f / frameSpeed)
    {
        framesCounter = 0.0f;
        currentFrame += 1;
        if (currentFrame > 6)
        {
            isFinished = true;
            currentFrame = 7;
        }
    }
}

void ExplosionFX::Draw()
{
    Rectangle sourceRec = {currentFrame * texture.width / 16, 0, (float)texture.width / 16, (float)texture.height};
    Rectangle destRec = {
        position.x - (texture.width / 16.0f * scale) / 2 + offset.x,
        position.y - (texture.height * scale) / 2 + offset.y,
        texture.width / 16.0f * scale,
        texture.height * scale};
    Vector2 origin = {0, 0}; // No need to offset further since we adjusted `destRec`
    DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, WHITE);
}

bool ExplosionFX::IsFinished() const
{
    return isFinished;
}