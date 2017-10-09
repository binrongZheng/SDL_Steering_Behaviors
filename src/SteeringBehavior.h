#pragma once
#include "Agent.h"
#include "Vector2D.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>
using namespace std;

class Agent;
struct Path;

class SteeringBehavior
{
public:
	SteeringBehavior();
	~SteeringBehavior();
	Vector2D KinematicSeek(Agent *agent, Vector2D target, float dtime);
	Vector2D KinematicSeek(Agent *agent, Agent *target, float dtime);
	Vector2D KinematicFlee(Agent *agent, Vector2D target, float dtime);
	Vector2D KinematicFlee(Agent *agent, Agent *target, float dtime);

	/* Add here your own Steering Behavior functions declarations */
	Vector2D Seek(Agent *agent, Vector2D target, float dtime);
	Vector2D Seek(Agent *agent, Agent *target, float dtime);
	Vector2D Flee(Agent *agent, Vector2D target, float dtime);
	Vector2D Flee(Agent *agent, Agent *target, float dtime);	
	Vector2D Arrive(Agent *agent, Vector2D target, float dtime, float radiArea);
	Vector2D Arrive(Agent *agent, Agent *target, float dtime, float radiArea);
	Vector2D Wander(Agent *agent, float WanderMaxAngleChange, float  wanderCircleOffset, float wanderCircleRadius, float dtime);
	Vector2D Evade(Agent *agent, Agent *zombie, float dtime);
	Vector2D PathFollow(Agent *agent, Path p, float dtime);
	Vector2D Pursue(Agent *agent, Agent* target, float dtime);
	Vector2D AvoidCollision(Agent *agent, std::vector<Agent*> agents, float dtime);
	//Vector2D AvoidCollision(Agent *agent, float dtime);

	float RandomBinomial();
	
};
