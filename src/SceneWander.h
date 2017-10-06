#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class SceneWander :
	public Scene
{
public:
	SceneWander();
	~SceneWander();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
	
public:
	// Wander fields
	float WanderMaxAngleChange;
	int wanderCircleOffset;
	int wanderCircleRadius;
	Vector2D wanderCircleCenter = {};
	Vector2D wanderDisplacementVector = {};
	
};

