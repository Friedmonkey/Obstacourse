#pragma once

#include "Settings.h"

class Wall {
public:
    Wall(Vector2 start, Vector2 end);

    void Draw();
    bool CheckCollision(Vector2 point);
    Rectangle GetRectangle();

    Vector2 position;
    Vector2 size;
};
