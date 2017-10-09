#include "ScenePursue.h"

using namespace std;

ScenePursue::ScenePursue()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);

	Agent *zombie = new Agent;
	zombie->setPosition(Vector2D(90, 90));
	zombie->setTarget(Vector2D(120,120));
	zombie->setColor(0, 0, 255, 255);
	zombie->loadSpriteTexture("../res/zombie1.png", 8);
	zombies.push_back(zombie);
	
}

ScenePursue::~ScenePursue()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}


void ScenePursue::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[0]->setTarget(target);
		}
		break;
	default:
		break;
	}

	Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], agents[0]->getTarget(), dtime);
	agents[0]->update(steering_force, dtime, event);
	Vector2D Pursue_force = zombies[0]->Behavior()->Pursue(zombies[0], agents[0],  dtime);
		
	zombies[0]->update(Pursue_force, dtime, event);
}

void ScenePursue::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
	zombies[0]->draw();
}

const char* ScenePursue::getTitle()
{
	return "SDL Steering Behaviors :: Arrival Demo";
}