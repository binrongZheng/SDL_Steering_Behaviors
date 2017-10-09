#include "SceneCollisionAvoidance.h"

using namespace std;


SceneCollisionAvoidance::SceneCollisionAvoidance()
{
	agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);

	//enemics
	Agent *enemy = new Agent;
	enemy->setPosition(Vector2D(300, 150));
	enemy->setTarget(Vector2D(640, 360));
	enemy->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(enemy);
	target = Vector2D(640, 360);
}

SceneCollisionAvoidance::~SceneCollisionAvoidance()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneCollisionAvoidance::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agent->setTarget(target);
		}
		break;
	default:
		break;
	}

	//Vector2D collision_force = agent->Behavior()->AvoidCollision(agent, dtime);
	Vector2D collision_force = agent->Behavior()->AvoidCollision(agent, agents, dtime);
	agent->update(collision_force, dtime, event);

}

void SceneCollisionAvoidance::draw()
{

	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agent->draw();
	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->draw();
	}
}

const char* SceneCollisionAvoidance::getTitle()
{
	return "SDL Steering Behaviors :: Collision Avoidance Demo";
}