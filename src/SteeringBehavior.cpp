#include "SteeringBehavior.h"
#include <time.h>
#include <vector>

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

Vector2D SteeringBehavior::Wander(Agent *agent, float WanderMaxAngleChange, float  wanderCircleOffset, float wanderCircleRadius,float dtime)
{
																							
	srand(time(NULL));
	float wA = WanderMaxAngleChange*RandomBinomial();
			
	//calculem centre del cercle
	Vector2D circleCenter = agent->position + Vector2D::Normalize(agent->velocity) * wanderCircleOffset;
	draw_circle(TheApp::Instance()->getRenderer(), (int)circleCenter.x, (int)circleCenter.y, wanderCircleRadius, 0, 150, 0, 255);

	//calculem el punt del cercle on volem anar	
	Vector2D newTarget;
	newTarget.x = circleCenter.x + wanderCircleRadius*cosf(wA * DEG2RAD);
	newTarget.y = circleCenter.y + wanderCircleRadius*sinf(wA * DEG2RAD);
	draw_circle(TheApp::Instance()->getRenderer(), (int)newTarget.x, (int)newTarget.y, 15, 255, 0, 0, 255);
		
	return Seek(agent, newTarget, dtime);
}


Vector2D SteeringBehavior::Evade(Agent *agent, Agent *zombie, float dtime)
{
	Vector2D distance = agent->position - zombie->position;
	float Ndistance=sqrt(distance.x*distance.x+distance.y*distance.y);
	float T = Ndistance / agent->max_velocity;

	Vector2D futurePosition = agent->position + agent->velocity*T;

	return Flee(zombie, futurePosition, dtime);
}
Vector2D SteeringBehavior::Pursue(Agent * agent, Agent * target, float dtime)
{								//agent -> zombie, target -> objectiu / humà
	Vector2D distance = target->position - agent->position;
	float Ndistance = sqrt(distance.x*distance.x + distance.y*distance.y);
	float T = Ndistance / target->max_velocity;

	float MaxLookAheadTime = 3;
	if (T > MaxLookAheadTime) {
		T = MaxLookAheadTime;
	}

	Vector2D futurePosition = target->position + target->velocity*T;
	
	draw_circle(TheApp::Instance()->getRenderer(), (int)futurePosition.x, (int)futurePosition.y, 15, 255, 0, 0, 255);
	

	return Seek(agent, futurePosition, dtime);
}

float SteeringBehavior::RandomBinomial()
{
	return ((float)rand() / (RAND_MAX))
		- ((float)rand() / (RAND_MAX));
}

Vector2D SteeringBehavior::PathFollow(Agent * agent, Path p, float dtime)
{
	Vector2D predictedTarget;
	
	while(agent->currentTargetIndex<5){
		if (abs((agent->position - p.pathArray[agent->currentTargetIndex]).Length())<20&& agent->currentTargetIndex!=4) {
			agent->currentTargetIndex++;
		}
		return Seek(agent, p.pathArray[agent->currentTargetIndex], dtime);

	}
	
}


Vector2D SteeringBehavior::AvoidCollision(Agent * agent, std::vector<Agent*> agents, float dtime)	//agents-> tots els enemics
//Vector2D SteeringBehavior::AvoidCollision(Agent * agent, float dtime)	//agents-> tots els enemics
{
	float shortestDistance = 1000;
	float coneHalfAngle = 40;
	float coneHeight = 100;
	Agent nearestAgent = Agent();	//guarrada... pero sino no puc fer el return
	Vector2D coneBase = agent->position+Vector2D::Normalize(agent->velocity)*coneHeight;
	bool collisionDetected = false;

	Vector2D finalForce;

	for (std::vector<Agent*>::iterator it = agents.begin(); it != agents.end(); ++it) {
		
		float currDist = Vector2D::Distance(agent->position, (*it)->position);
		if (Vector2DUtils::IsInsideCone((*it)->position, agent->position, coneBase, coneHalfAngle)) {
			if (currDist < shortestDistance) {
				nearestAgent = *(*it);
				shortestDistance = currDist;
				collisionDetected = true;
				draw_circle(TheApp::Instance()->getRenderer(), 500, 400, 15, 255, 0, 0, 255);
			}
		}
	}
	if (collisionDetected) {
		return Flee(agent, nearestAgent.position, dtime);
	}
	else {
		return Seek(agent, agent->getTarget(), dtime);
	}

	//return Seek(agent, agent->getTarget(), dtime);


}
