#pragma once

#include "Settings.h"
#include <Vector>
#include <memory>

#include "Wall.h"
#include "Agent.h"


class Game
{
public:
	Game();
	void Draw();
	void Update();
	void BuildLevel1();
private:


	std::vector<Wall> walls;
	static std::unique_ptr<Agent> agent;

	static std::unique_ptr<b2World> world;
};

