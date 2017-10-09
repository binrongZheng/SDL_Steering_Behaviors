#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class SceneCombination :
	public Scene
{
public:
	SceneCombination();
	~SceneCombination();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
	
public:
	Path p;	
};

