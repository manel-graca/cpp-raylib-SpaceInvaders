#include "game.hpp"
#include <raylib.h>
int main(int, char **)
{
    InitWindow(450, 650, "Space Invaders");
    SetTargetFPS(60);

    Game game = Game();

    while (WindowShouldClose() == false)
    {
        game.Update();
        BeginDrawing();
        ClearBackground(BLACK);
        game.Draw();
        EndDrawing();
    }

    return 0;
}
