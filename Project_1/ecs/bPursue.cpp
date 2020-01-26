#include "bPursue.h"

#include <assert.h>

#include "cTransform.h"
#include "cVelocity.h"

PursueBehaviour::PursueBehaviour(Entity* agent, Entity* target) : mAgent(agent), mTarget(target)
{
}

PursueBehaviour::~PursueBehaviour(void)
{
}

void PursueBehaviour::Update(float dt)
{
	assert(mAgent);
	assert(mTarget);

	// Gets nessesary components from entites
	Transform* agentTransform = mAgent->GetComponent<Transform>();
	Transform* targetTransform = mTarget->GetComponent<Transform>();
	Velocity* agentVelocity = mAgent->GetComponent<Velocity>();

	if (agentTransform == 0 || targetTransform == 0 || agentVelocity == 0) return;

	glm::vec3 desiredVelocity = glm::normalize(targetTransform->position - agentTransform->position);

	desiredVelocity *= MAXVELOCITY;

	glm::vec3 steer;
	steer.x = desiredVelocity.x - agentVelocity->vx;
	steer.y = desiredVelocity.y - agentVelocity->vy;

	agentVelocity->vx += steer.x * dt;
	agentVelocity->vy += steer.y * dt;

	if (agentVelocity->vx > MAXVELOCITY)
		agentVelocity->vx = MAXVELOCITY;

	if (agentVelocity->vy > MAXVELOCITY)
		agentVelocity->vy = MAXVELOCITY;
}

