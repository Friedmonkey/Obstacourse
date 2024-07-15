// Obstacourse.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Settings.h"
#include "Agent.h";
#include "Wall.h"

int main()
{
    InitWindow(SW, SH, "Obstacle Course lol");
    SetTargetFPS(60);

    Agent agent = Agent({SW2, SH2}, 60.0f);
    std::vector<Wall> walls = {
    Wall({100, 100}, {600, 20}),
    Wall({100, 500}, {620, 20}),
    Wall({100, 100}, {20, 400}),
    Wall({700, 100}, {20, 400})
    };

    while (!WindowShouldClose())
    {
        BeginDrawing();

        agent.Update();
        agent.CheckCollisionWithWalls(walls);

        ClearBackground(RAYWHITE);

        agent.Draw();
        for (auto& wall : walls) {
            wall.Draw();
        }

        EndDrawing();
    }

    CloseWindow();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
