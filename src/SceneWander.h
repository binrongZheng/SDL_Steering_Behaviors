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
	int maxWanderAngle = 50;
	int wanderCircleOffset = 150;
	int wanderCircleRadius = 250;
	float* wanderAngle = new float;
	Vector2D wanderCircleCenter = {};
	Vector2D wanderDisplacementVector = {};
	
};

