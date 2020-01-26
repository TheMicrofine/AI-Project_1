#include "bApproach.h"

#include <assert.h>

#include "cTransform.h"
#include "cVelocity.h"
#include <iostream>
#include <math.h>

ApproachBehaviour::ApproachBehaviour(Entity* agent, Entity* target) : mAgent(agent), mTarget(target)
{
}

ApproachBehaviour::~ApproachBehaviour(void)
{
}

void ApproachBehaviour::Update(float dt)
{
	assert(mAgent);
	assert(mTarget);

	// Gets nessesary components from entites
	Transform* agentTransform = mAgent->GetComponent<Transform>();
	Transform* targetTransform = mTarget->GetComponent<Transform>();
	Velocity* agentVelocity = mAgent->GetComponent<Velocity>();

	if (agentTransform == 0 || targetTransform == 0 || agentVelocity == 0) return;

	glm::vec3 desiredVelocity = glm::normalize(targetTransform->position - agentTransform->position);

	glm::vec3 distance = targetTransform->position - agentTransform->position;

	distance.x = fabs(distance.x);
	distance.y = fabs(distance.y);

	if (distance.x < SLOWINGRADIUS && distance.y < SLOWINGRADIUS)
	{
		desiredVelocity = desiredVelocity * MAXVELOCITY * (distance / SLOWINGRADIUS);
	}
	else
	{
		desiredVelocity *= MAXVELOCITY;
	}

	glm::vec3 steer;

	if (distance.x < MAINTAINRADUIS && distance.y < MAINTAINRADUIS)
	{
		agentVelocity->vx = 0;
		agentVelocity->vy = 0;
	}
	else
	{

		steer.x = desiredVelocity.x - agentVelocity->vx;
		steer.y = desiredVelocity.y - agentVelocity->vy;
		
		agentVelocity->vx += steer.x * dt;
		agentVelocity->vy += steer.y * dt;
	}

	if (agentVelocity->vx > MAXVELOCITY)
		agentVelocity->vx = MAXVELOCITY;

	if (agentVelocity->vy > MAXVELOCITY)
		agentVelocity->vy = MAXVELOCITY;
}

