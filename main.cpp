#include <raylib.h>
int main(int, char **)
{
    InitWindow(450, 650, "Space Invaders");
    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }

    return 0;
}
