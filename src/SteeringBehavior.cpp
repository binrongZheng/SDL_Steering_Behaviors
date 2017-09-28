#include "SteeringBehavior.h"
#include <time.h>



SteeringBehavior::SteeringBehavior()
{
}


SteeringBehavior::~SteeringBehavior()
{
}

Vector2D SteeringBehavior::KinematicSeek(Agent *agent, Vector2D target, float dtime)
{
	Vector2D steering = target - agent->position;
	steering.Normalize();
	return steering * agent->max_velocity;
}

Vector2D SteeringBehavior::KinematicSeek(Agent *agent, Agent *target, float dtime)
{
	return KinematicSeek(agent, target->position, dtime);
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Vector2D target, float dtime)
{
	Vector2D steering = agent->position - target;
	steering.Normalize();
	return steering * agent->max_velocity;
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Agent *target, float dtime)
{
	return KinematicFlee(agent, target->position, dtime);
}


/* Add here your own Steering Behavior functions definitions */
/*


Vector2D SteeringBehavior::Seek(Agent *agent, Vector2D target, float dtime)
{
	return Vector2D(0, 0);

}
*/

Vector2D SteeringBehavior::Seek(Agent *agent, Vector2D target, float dtime)
{
	Vector2D dv = target - agent->position;
	dv.Normalize();
	dv *= agent->max_velocity;
	Vector2D sf = dv - agent->velocity;
	sf /= agent->getMaxVelocity();

	return sf * agent->max_force;
}

Vector2D SteeringBehavior::Seek(Agent *agent, Agent *target, float dtime)
{
	return Seek(agent, target->position, dtime);
}


Vector2D SteeringBehavior::Flee(Agent *agent, Vector2D target, float dtime)
{
	Vector2D dv = agent->position- target ;
	dv.Normalize();
	dv *= agent->max_velocity;
	Vector2D sf = dv - agent->velocity;
	sf /= agent->getMaxVelocity();

	return sf * agent->max_force;
}

Vector2D SteeringBehavior::Flee(Agent *agent, Agent *target, float dtime)
{
	return Flee(agent, target->position, dtime);
}

Vector2D SteeringBehavior::Arrive(Agent *agent, Vector2D target, float radiArea, float dtime)
{

	Vector2D dv = target- agent->position;
	float Factor;
	float distance = sqrt(dv.x*dv.x+dv.y*dv.y);
	if (distance > radiArea) {
		dv.Normalize();
		dv *= agent->max_velocity;
	}
	else{
		
		dv.Normalize();
		Factor = distance / radiArea;		
		dv *= agent->max_velocity*Factor;
	}

	Vector2D sf = dv - agent->velocity;
	sf /= agent->getMaxVelocity();
	
	return sf * agent->max_force;
}

Vector2D SteeringBehavior::Arrive(Agent *agent, Agent *target, float dtime,float radiArea)
{
	return Arrive(agent, target->position, dtime, radiArea);
}

Vector2D SteeringBehavior::Wander(Agent *agent, float angle, float *wanderAngle, int wanderMaxChangediArea, float  wanderCircleOffset, float wanderCircleRadius,float dtime)
{
	srand(time(NULL));
	wanderAngle += -wanderMaxChangediArea+rand() % (wanderMaxChangediArea*2);
	//centre
	Vector2D c;
	c.x = wanderCircleOffset*cos(angle);
	c.y = wanderCircleOffset*sin(angle);

	Vector2D Target;
	
	return c;
}


Vector2D SteeringBehavior::Evade(Agent *agent, Vector2D target, float radiArea, float dtime)
{

	Vector2D dv = target - agent->position;
	float Factor;
	float distance = sqrt(dv.x*dv.x + dv.y*dv.y);
	if (distance > radiArea) {
		dv.Normalize();
		dv *= agent->max_velocity;
	}
	else {

		dv.Normalize();
		Factor = distance / radiArea;
		dv *= agent->max_velocity*Factor;
	}

	Vector2D sf = dv - agent->velocity;
	sf /= agent->getMaxVelocity();

	return sf * agent->max_force;
}
Vector2D SteeringBehavior::Evade(Agent *agent, Agent *target, float dtime, float radiArea)
{
	return Arrive(agent, target->position, dtime, radiArea);
}
