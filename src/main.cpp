#include "game.hpp"
#include <raylib.h>
int main(int, char **)
{
    InitWindow(450, 650, "Space Invaders");
    SetTargetFPS(60);

    Image starsBg = LoadImage("assets/graphics/stars_bg.png");
    Texture2D starsBgTexture = LoadTextureFromImage(starsBg);
    UnloadImage(starsBg);

    Game game = Game();

    while (WindowShouldClose() == false)
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            if (!game.IsPlaying())
            {
                game.SetPlaying(true);
            }
        }

        game.Update();
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(starsBgTexture, 0, 0, {255, 255, 255, 70});

        if (!game.IsPlaying())
        {
            DrawText("PRESS SPACE TO START", GetScreenWidth() / 2 - MeasureText("PRESS SPACE TO START", 30) / 2, GetScreenHeight() / 2, 30, WHITE);
        }

        game.Draw();
        EndDrawing();
    }

    return 0;
}
