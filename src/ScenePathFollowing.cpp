#include "ScenePathFollowing.h"

using namespace std;
class agent;
Path pas;

ScenePathFollowing::ScenePathFollowing()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	pas.pathArray[0] = Vector2D(100, 150); pas.pathArray[1] = Vector2D(200, 200); pas.pathArray[2] = Vector2D(300, 400); pas.pathArray[3] = Vector2D(400, 400); pas.pathArray[4] = Vector2D(500, 500);
}

ScenePathFollowing::~ScenePathFollowing()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void ScenePathFollowing::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	/*switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT){		}
		break;
	default:
		break;
	}*/

	Vector2D steering_force = agents[0]->Behavior()->PathFollow(agents[0], pas, dtime);
	agents[0]->update(steering_force, dtime, event);
}

void ScenePathFollowing::draw()
{
	//draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	for (int i = 1; i < 6;i++) {
		draw_circle(TheApp::Instance()->getRenderer(), (int)pas.pathArray[i-1].x, (int)pas.pathArray[i-1].y, 15, 200, 200, 0, 255);
		if(i!=5)		SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)pas.pathArray[i].x, (int)pas.pathArray[i].y, (int)pas.pathArray[i-1].x, (int)pas.pathArray[i-1].y);
	}
	agents[0]->draw();
}
//sdjksfjdlsfj
const char* ScenePathFollowing::getTitle()
{
	return "SDL Steering Behaviors :: Seek Demo";
}