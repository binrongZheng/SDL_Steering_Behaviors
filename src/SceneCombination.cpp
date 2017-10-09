#include "SceneCombination.h"

using namespace std;

SceneCombination::SceneCombination()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640,360));
	agent->setTarget(Vector2D(640, 360));
	agent->setMass(0.035);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
		
	target = Vector2D(640, 360);
	p.pathArray[0] = Vector2D(100, 150); p.pathArray[1] = Vector2D(200, 200); p.pathArray[2] = Vector2D(300, 400); p.pathArray[3] = Vector2D(400, 400); p.pathArray[4] = Vector2D(500, 500);
}

SceneCombination::~SceneCombination()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneCombination::update(float dtime, SDL_Event *event)
{
	
	Vector2D steering_force1 = agents[0]->Behavior()->PathFollow(agents[0], p, dtime);
	agents[0]->update(steering_force1, dtime, event);
}

void SceneCombination::draw()
{
	for (int i = 1; i < 6; i++) {
		draw_circle(TheApp::Instance()->getRenderer(), (int)p.pathArray[i - 1].x, (int)p.pathArray[i - 1].y, 15, 200, 200, 0, 255);
		if (i != 5)		SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)p.pathArray[i].x, (int)p.pathArray[i].y, (int)p.pathArray[i - 1].x, (int)p.pathArray[i - 1].y);
	}
	agents[0]->draw();
}

const char* SceneCombination::getTitle()
{
	return "SDL Steering Behaviors :: Wander Demo";
}