#pragma once

#include <Box2D/Box2D.h>
#include <Vector>

#include "Settings.h"

#include "Wall.h"

class Agent
{
public:
	void Initialize(b2World *pWorld, Vector2 pos);

	void Draw();
	void Update();

protected:
	void GetTriangle(Vector2 *p1, Vector2 *p2, Vector2 *p3);

private:
	void RotateLeft(float amount);
	void RotateRight(float amount);

	b2Body* body{};

	float size = 60;
	float moveSpeed		{500.0f};
	float rotateSpeed	{30.0f};
};

