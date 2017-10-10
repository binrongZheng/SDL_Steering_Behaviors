#include "SceneCombination.h"

using namespace std;

SceneCombination::SceneCombination()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640,360));
	agent->setTarget(Vector2D(100, 150));
	agent->setMass(0.035);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);

	Agent *zombie = new Agent;
	zombie->setPosition(Vector2D(750, 725));	
	zombie->setColor(0, 0, 255, 255);
	zombie->loadSpriteTexture("../res/zombie1.png", 8);
	zombies.push_back(zombie);
			
	target = Vector2D(640, 360);
	p.pathArray[0] = Vector2D(100, 150); p.pathArray[1] = Vector2D(400, 400); p.pathArray[2] = Vector2D(400, 550); p.pathArray[3] = Vector2D(300, 700); p.pathArray[4] = Vector2D(1200, 700);
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
	Vector2D steering_force2 = agents[0]->Behavior()->Arrive(agents[0], p.pathArray[agents[0]->currentTargetIndex], 250, dtime);
	Vector2D steering_force3 = agents[0]->Behavior()->AvoidCollision(agents[0], zombies, dtime);
	//fem un weighted blending
	agents[0]->update(steering_force1*0.25 + steering_force2*3 + steering_force3, dtime, event); //igualment gira pq el arrive ja et mou cap al punt tmb.
		
}

void SceneCombination::draw()
{
	//Pintem path
	for (int i = 1; i < 6; i++) {
		draw_circle(TheApp::Instance()->getRenderer(), (int)p.pathArray[i - 1].x, (int)p.pathArray[i - 1].y, 15, 200, 200, 0, 255);
		if (i != 5)		SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)p.pathArray[i].x, (int)p.pathArray[i].y, (int)p.pathArray[i - 1].x, (int)p.pathArray[i - 1].y);
	}
	//Pintem cercle de arrive
	draw_circle(TheApp::Instance()->getRenderer(), (int)p.pathArray[agents[0]->currentTargetIndex].x, (int)p.pathArray[agents[0]->currentTargetIndex].y, 250, 0, 0, 255, 255);
	
	//pintem el personatge
	agents[0]->draw();
	zombies[0]->draw();
		
}

const char* SceneCombination::getTitle()
{
	return "SDL Steering Behaviors :: Combination Demo";
}