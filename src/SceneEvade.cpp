#include "SceneEvade.h"

using namespace std;

SceneEvade::SceneEvade()
{


	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);

	Agent *zombie = new Agent;
	zombie->setPosition(Vector2D(90, 90));
	zombie->setTarget(Vector2D(120, 120));
	zombie->setColor(0, 0, 255, 255);
	zombie->loadSpriteTexture("../res/zombie1.png", 8);
	zombies.push_back(zombie);
	/*Agent *agent = new Agent;	
	agent->setMass(0.6f);
	agent->setPosition(Vector2D(640, 320));
	agent->setColor(0, 0, 255, 255);
	agent->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(agent);
	agent = new Agent();
	agent->setPosition(Vector2D(600, 50));
	agent->setTarget(Vector2D(900, 650));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(900, 650);*/
}

SceneEvade::~SceneEvade()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}


void SceneEvade::update(float dtime, SDL_Event *event)
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
	//agents[0]->setTarget(agents[1]->getPosition());
	Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], agents[0]->getTarget(), dtime);
	agents[0]->update(steering_force, dtime, event);
	
	steering_force = agents[0]->Behavior()->Evade(agents[1], agents[0], dtime);
	steering_force = zombies[0]->Behavior()->Evade(agents[0], zombies[0], dtime);
	zombies[0]->update(steering_force, dtime, event);
}

void SceneEvade::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
	//agents[1]->draw();
	zombies[0]->draw();
}

const char* SceneEvade::getTitle()
{
	return "SDL Steering Behaviors :: Arrival Demo";
}