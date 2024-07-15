#include "Agent.h"
#include <RayMath.h>

Agent::Agent(Vector2 pos, float size)
{
    position.x = pos.x;
    position.y = pos.y;

    this->size = size;
    this->moveSpeed = size / 12;
    this->rotateSpeed = size / 24;
}

void Agent::Draw()
{
	Vector2 p1, p2, p3;
	GetTriangle(&p1, &p2, &p3);
	DrawTriangle(p1,p2,p3, CORNFLOWERBLUE);
    DrawCircleV(position, size*0.1f, RED);
}

void Agent::Update()
{

    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN))
    {
        Vector2 localP1 = { 0, -moveSpeed };
        float rad = direction * DEG2RAD;
        Vector2 rotatedP1 = Vector2Rotate(localP1, rad);

        if (IsKeyDown(KEY_UP))
        {
            position = Vector2Add(position, rotatedP1);
        }
        else
        {
            position = Vector2Subtract(position, rotatedP1);
        }
    }

    if (IsKeyDown(KEY_LEFT))
    {
        direction -= rotateSpeed;
        if (direction < 0)
        {
            direction = 360.0f - fabsf(direction);
        }
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        direction += rotateSpeed;
        if (direction > 360.0f)
        {
            direction = direction - 360.0f;
        }
    }
    //direction += 20.0f * GetFrameTime();
    //if (direction > 360.0f) direction -= 360.0f; // Wrap around the rotation value
}


void Agent::CheckCollisionWithWalls(std::vector<Wall> &walls) 
{
    Vector2 p1, p2, p3;
    GetTriangle(&p1, &p2, &p3);
    std::vector<Vector2> poses { p1, p2, p3 };

    for (Wall& wall : walls) {
        for (Vector2 pos : poses)
        {
            if (wall.CheckCollision(pos)) {
                ResolveCollision(wall, pos);
            }
        }
    }
}

void Agent::ResolveCollision(Wall& wall, Vector2 collisionPoint) {
    Rectangle rect = wall.GetRectangle();

    // Determine the closest side of the rectangle
    float leftDist = collisionPoint.x - rect.x;
    float rightDist = (rect.x + rect.width) - collisionPoint.x;
    float topDist = collisionPoint.y - rect.y;
    float bottomDist = (rect.y + rect.height) - collisionPoint.y;

    // Find the minimum distance
    float minDist = fmin(fmin(leftDist, rightDist), fmin(topDist, bottomDist));

    // Adjust the position based on the minimum distance side
    if (minDist == leftDist) {
        position.x -= leftDist;  // Move left
    }
    else if (minDist == rightDist) {
        position.x += rightDist;  // Move right
    }
    else if (minDist == topDist) {
        position.y -= topDist;  // Move up
    }
    else if (minDist == bottomDist) {
        position.y += bottomDist;  // Move down
    }

    // To simulate sliding along the wall, ensure the agent cannot move further into the wall
    // Adjust position along the direction perpendicular to the collision normal
    if (minDist == leftDist || minDist == rightDist) {
        // Sliding vertically
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN)) {
            Vector2 localP1 = { 0, -moveSpeed };
            float rad = direction * DEG2RAD;
            Vector2 rotatedP1 = Vector2Rotate(localP1, rad);

            if (IsKeyDown(KEY_UP)) {
                position = Vector2Add(position, rotatedP1);
            }
            else {
                position = Vector2Subtract(position, rotatedP1);
            }
        }
    }
    else if (minDist == topDist || minDist == bottomDist) {
        // Sliding horizontally
        if (IsKeyDown(KEY_LEFT)) {
            direction -= rotateSpeed;
            if (direction < 0) {
                direction = 360.0f - fabsf(direction);
            }
        }
        else if (IsKeyDown(KEY_RIGHT)) {
            direction += rotateSpeed;
            if (direction > 360.0f) {
                direction = direction - 360.0f;
            }
        }
    }
}


void Agent::GetTriangle(Vector2* p1, Vector2* p2, Vector2* p3)
{
    const double sqrt = 0.86602540378;
    float halfHeight = sqrt * size;

    // Points of an equilateral triangle centered at (0,0)
    Vector2 localP1 = { 0, -halfHeight };
    Vector2 localP2 = { -size / 2, halfHeight / 2 };
    Vector2 localP3 = { size / 2, halfHeight / 2 };

    // Rotate points by direction
    float rad = direction * DEG2RAD;
    Vector2 rotatedP1 = Vector2Rotate(localP1, rad);
    Vector2 rotatedP2 = Vector2Rotate(localP2, rad);
    Vector2 rotatedP3 = Vector2Rotate(localP3, rad);

    // Translate points to the agent's position
    *p1 = Vector2Add(position, rotatedP1);
    *p2 = Vector2Add(position, rotatedP2);
    *p3 = Vector2Add(position, rotatedP3);
}


