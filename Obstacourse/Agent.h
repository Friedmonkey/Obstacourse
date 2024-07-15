#pragma once
#include "Settings.h"
#include "Wall.h"
#include <Vector>

class Agent
{
public:
	Agent(Vector2 pos, float size = 120);
	void Draw();
	void Update();
	void CheckCollisionWithWalls(std::vector<Wall> &walls);

protected:
	void GetTriangle(Vector2 *p1, Vector2 *p2, Vector2 *p3);

private:

	void ResolveCollision(Wall& wall, Vector2 position);
	Vector2 position;

	float direction = 90;
	float size = 120;
	float moveSpeed = 5.0f;
	float rotateSpeed = 2.5f;
};

