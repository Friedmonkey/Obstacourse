#include "Agent.h"
#include <RayMath.h>

void Agent::Initialize(b2World* pWorld, Vector2 pos)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x, pos.y);

    bodyDef.angularDamping = 5.0f;

    this->body = pWorld->CreateBody(&bodyDef);

    Vector2 p1,p2,p3;
    GetTriangle(&p1,&p2,&p3);
    p1 = Vector2Subtract(pos, p1);
    p2 = Vector2Subtract(pos, p2);
    p3 = Vector2Subtract(pos, p3);

    b2Vec2 points[3] 
    {
        ConvertToBox(p1),
        ConvertToBox(p2),
        ConvertToBox(p3),
    };

    b2PolygonShape dynamicBox;
    dynamicBox.Set(points, 3);
    //dynamicBox.SetAsBox(0.9, 1);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 10.0f;

    body->CreateFixture(&fixtureDef);
}

void Agent::Draw()
{
	Vector2 p1, p2, p3;
	GetTriangle(&p1, &p2, &p3);
	DrawTriangle(p1,p2,p3, CORNFLOWERBLUE);

    b2Vec2 pos = body->GetPosition();
    DrawCircleV(ConvertToRay(pos), size * 0.1f, RED);
}

void Agent::Update()
{

    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN))
    {
        float rad = body->GetAngularVelocity();
        Vector2 pos = ConvertToRay(body->GetPosition());


        Vector2 imp = { 0, moveSpeed };

        if (IsKeyDown(KEY_UP))
        {
            imp.y = -moveSpeed;
        }


        Vector2 impu = Vector2Rotate(imp, rad);
        b2Vec2 impulse = ConvertToBox(impu);

        //Vector2 poi = { 0, moveSpeed };
        //Vector2 poin = Vector2Rotate(poi, rad);
        //b2Vec2 point = ConvertToBox(poin);

        float angle = atan2f(pos.y - impulse.y, pos.x - impulse.x);

        float newX = -cosf(angle) * moveSpeed;
        float newY = -sinf(angle) * moveSpeed;

        body->ApplyForceToCenter(b2Vec2(newX, newY), true);
        //impu = Vector2Add(pos, impu);
        //poin = Vector2Add(pos, poin);

        //DrawCircleV(poin, size * 2.5f, PURPLE);
        //DrawCircleV(impu, size * 2.5f, PURPLE);


        //if (IsKeyDown(KEY_UP))
        //{
        //    body->ApplyLinearImpulse(impulse, point, true);
        //    //position = Vector2Add(position, rotatedP1);

        //    impu = Vector2Add(pos, impu);
        //    poin = Vector2Add(pos, poin);

        //    DrawCircleV(impu, size * 0.5f, GREEN);
        //    DrawCircleV(poin, size * 0.5f, BLUE);
        //}
        //else
        //{
        //    body->ApplyLinearImpulse(point, impulse, true);

        //    impu = Vector2Add(pos, impu);
        //    poin = Vector2Add(pos, poin);

        //    DrawCircleV(poin, size * 0.5f, GREEN);
        //    DrawCircleV(impu, size * 0.5f, BLUE);
        //    //position = Vector2Subtract(position, rotatedP1);
        //}
    }

    if (IsKeyDown(KEY_LEFT))
    {
        RotateLeft(rotateSpeed);
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        RotateRight(rotateSpeed);
    }
    //direction += 20.0f * GetFrameTime();
    //if (direction > 360.0f) direction -= 360.0f; // Wrap around the rotation value
}

void Agent::RotateLeft(float amount)
{
    body->ApplyAngularImpulse(-amount, false);
    //body->ApplyAngularImpulse((amount*100 * DEG2RAD), false);
    //direction -= amount;
    //if (direction < 0)
    //{
    //    direction = 360.0f - fabsf(direction);
    //}
}

void Agent::RotateRight(float amount)
{
    body->ApplyAngularImpulse(amount, false);

    //body->ApplyAngularImpulse(-(amount*100 * DEG2RAD), false);

    //direction += amount;
    //if (direction > 360.0f)
    //{
    //    direction = direction - 360.0f;
    //}
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

void Agent::ResolveCollision(Wall& wall, Vector2 collisionPoint) 
{
    //// Get the rectangle of the wall
    //Rectangle rect = wall.GetRectangle();

    //// Determine the distances from the collision point to each side of the wall
    //float leftDist = collisionPoint.x - rect.x;
    //float rightDist = (rect.x + rect.width) - collisionPoint.x;
    //float topDist = collisionPoint.y - rect.y;
    //float bottomDist = (rect.y + rect.height) - collisionPoint.y;

    //// Find the minimum distance to each side
    //float minDistX = fmin(leftDist, rightDist);
    //float minDistY = fmin(topDist, bottomDist);

    //float buffer = 2;

    //// Adjust the position based on the minimum distance side
    //if (minDistX < minDistY) //if the x distance is closer
    //{ //handle x
    //    // Horizontal collision (left or right)
    //    if (minDistX == leftDist) // did we hit a right wall
    //    {
    //        position.x -= leftDist+buffer;  // Move left by the distance to the left side
    //        if (direction > 90)
    //            RotateRight(minDistX);
    //        else
    //            RotateLeft(minDistX);
    //    }
    //    else //did we hit a left wall
    //    {
    //        position.x += rightDist;  // Move right by the distance to the right side
    //        //RotateLeft(rightDist);
    //        if (direction > 90)
    //            RotateLeft(minDistX);
    //        else
    //            RotateRight(minDistX);
    //    }
    //}
    //else //if the y distance is closer
    //{ //handle y
    //    // Vertical collision (top or bottom)
    //    if (minDistY == topDist) //did we hit a bottom wall
    //    {
    //        position.y -= topDist;  // Move up by the distance to the top side
    //        if (direction < 180)
    //            RotateLeft(minDistY);
    //        else
    //            RotateRight(minDistY);
    //    }
    //    else //did we hit a top wall
    //    {
    //        position.y += bottomDist;  // Move down by the distance to the bottom side
    //        if (direction < 180)
    //            RotateRight(minDistY);
    //        else
    //            RotateLeft(minDistY);
    //    }
    //}
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
    //float rad = direction * DEG2RAD;
    float rad = body->GetAngle();
    Vector2 rotatedP1 = Vector2Rotate(localP1, rad);
    Vector2 rotatedP2 = Vector2Rotate(localP2, rad);
    Vector2 rotatedP3 = Vector2Rotate(localP3, rad);

    b2Vec2 pos = body->GetPosition();
    Vector2 position = ConvertToRay(pos);

    // Translate points to the agent's position
    *p1 = Vector2Add(position, rotatedP1);
    *p2 = Vector2Add(position, rotatedP2);
    *p3 = Vector2Add(position, rotatedP3);
}


