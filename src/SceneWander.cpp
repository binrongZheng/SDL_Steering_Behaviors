#include "SceneWander.h"

using namespace std;

SceneWander::SceneWander()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640,360));
	agent->setTarget(Vector2D(640, 360));
	agent->setMass(0.035);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	
	
	maxWanderAngle = 120;
	wanderCircleOffset = 350;
	wanderCircleRadius = 130;
	*wanderAngle = 0.0f;
	wanderCircleCenter = {};
	wanderDisplacementVector = {};
	target = Vector2D(640, 360);
}

SceneWander::~SceneWander()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneWander::update(float dtime, SDL_Event *event)
{
	
	Vector2D steering_force = agents[0]->Behavior()->Wander(agents[0], wanderAngle, maxWanderAngle, wanderCircleOffset, wanderCircleRadius, dtime);
	agents[0]->update(steering_force, dtime, event);
}

void SceneWander::draw()
{
		agents[0]->draw();
}

const char* SceneWander::getTitle()
{
	return "SDL Steering Behaviors :: Wander Demo";
}