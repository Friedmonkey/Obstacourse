#include <iostream>
#include "Settings.h"
#include "Game.h";

int main()
{
    InitWindow(SW, SH, "Obstacle Course lol");
    SetTargetFPS(60);

    Game game = Game();


    while (!WindowShouldClose())
    {

        game.Update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}