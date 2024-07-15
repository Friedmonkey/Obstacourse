#include "Wall.h"
#include <RayMath.h>

Wall::Wall(Vector2 start, Vector2 end) {
    this->position = start;
    this->size = end;
}

void Wall::Draw() {
    DrawRectangleV(position, size, BLACK);
}

bool Wall::CheckCollision(Vector2 point)
{
    Rectangle rect = GetRectangle();
    return CheckCollisionPointRec(point, rect);
}

Rectangle Wall::GetRectangle()
{
    return { position.x, position.y, size.x, size.y };
}
