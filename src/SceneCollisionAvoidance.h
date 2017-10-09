#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"


class SceneCollisionAvoidance :
	public Scene
{
public:
	SceneCollisionAvoidance();
	~SceneCollisionAvoidance();
	
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();

private:
	Agent* agent;
	std::vector<Agent*> agents;
	Vector2D target;
};

