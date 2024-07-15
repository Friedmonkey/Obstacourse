#pragma once
#include "Settings.h"

class Agent
{
public:
	Agent(Vector2 pos);
	void Draw();
	void Update();

protected:
	void GetTriangle(Vector2 *p1, Vector2 *p2, Vector2 *p3);

private:
	Vector2 position;

	float direction = 90;
	float size = 120;
	float moveSpeed = 5.0f;
	float rotateSpeed = 2.5f;
};

