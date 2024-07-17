#pragma once

#include <Box2D/Box2D.h>
#include <Vector>

#include "Settings.h"

#include "Wall.h"

class Agent
{
public:
	Agent();
	Agent(Vector2 pos, float size = 120);

	void Initialize(b2World *pWorld);

	void Draw();
	void Update();
	void CheckCollisionWithWalls(std::vector<Wall> &walls);

protected:
	void GetTriangle(Vector2 *p1, Vector2 *p2, Vector2 *p3);

private:
	void RotateLeft(float amount);
	void RotateRight(float amount);
	void ResolveCollision(Wall& wall, Vector2 position);
	Vector2 position;

	b2Body* body{};

	float direction = 90;
	float size = 120;
	float moveSpeed = 5.0f;
	float rotateSpeed = 2.5f;
};

