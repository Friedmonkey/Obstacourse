#include "Game.h"

std::unique_ptr<Agent> Game::agent = nullptr;
std::unique_ptr<b2World> Game::world = nullptr;

Game::Game()
{
	b2Vec2 gravity = b2Vec2(0.0f, 0.1f);
	world = std::make_unique<b2World>(gravity);
	agent = std::make_unique<Agent>();

	agent->Initialize(world.get(), Vector2{ SW2, SH2 });
}

void Game::Draw()
{
	agent->Draw();

	//world.get()->DebugDraw();

	for (auto& wall : walls) {
		wall.Draw();
	}
}

void Game::Update()
{
	float timeStep = 1.0f / 60.0f;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	world->Step(timeStep, velocityIterations, positionIterations);

	agent->Update();
}

void Game::BuildLevel1()
{
    walls = {
		Wall({100, 100}, {600, 20}),
		Wall({100, 500}, {620, 20}),
		Wall({100, 100}, {20, 400}),
		Wall({700, 100}, {20, 400})
    };

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);

	groundBody->CreateFixture(&groundBox, 0.0f);



	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	b2Body* body = world->CreateBody(&bodyDef);


	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);


	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);

	float timeStep = 1.0f / 60.0f;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;


	//for (int32 i = 0; i < 60; ++i)
	//{
	//	world.Step(timeStep, velocityIterations, positionIterations);
	//	b2Vec2 position = body->GetPosition();
	//	float angle = body->GetAngle();
	//	printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	//}

}
