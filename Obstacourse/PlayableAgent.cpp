#include "Agent.h"
#include <RayMath.h>

void Agent::Initialize(b2World* pWorld, Vector2 pos)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x, pos.y);

    bodyDef.angularDamping = 5.0f;
    bodyDef.linearDamping = 4.0f;

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
        float rad = body->GetAngle();
        Vector2 pos = ConvertToRay(body->GetPosition());


        Vector2 imp = { 0, moveSpeed };

        if (IsKeyDown(KEY_UP))
        {
            imp.y = -moveSpeed;
        }


        Vector2 impu = Vector2Rotate(imp, rad);
        b2Vec2 impulse = ConvertToBox(impu);

        //float angle = atan2f(pos.y - impulse.y, pos.x - impulse.x);

        //float newX = -cosf(angle) * moveSpeed;
        //float newY = -sinf(angle) * moveSpeed;

        body->ApplyForceToCenter(impulse, true); //b2Vec2(newX, newY)
        
    }

    if (IsKeyDown(KEY_LEFT))
    {
        RotateLeft(rotateSpeed);
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        RotateRight(rotateSpeed);
    }
}

void Agent::RotateLeft(float amount)
{
    body->ApplyAngularImpulse(-amount, false);
}

void Agent::RotateRight(float amount)
{
    body->ApplyAngularImpulse(amount, false);
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


