#include "bPursue.h"
#include "cTransform.h"
#include "cVelocity.h"

#include <assert.h>


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
	Velocity* targetVelocity = mTarget->GetComponent<Velocity>();

	if (agentTransform == 0 || targetTransform == 0 || agentVelocity == 0) return;

	float magnitude = glm::length(targetTransform->position - agentTransform->position);

	int T = (int)magnitude / (int)MAXVELOCITY;

	glm::vec3 futurePosition;
	futurePosition.x = targetTransform->position.x + targetVelocity->vx * T;
	futurePosition.y = targetTransform->position.y + targetVelocity->vy * T;

	glm::vec3 desiredVelocity = glm::normalize(futurePosition - agentTransform->position);

	desiredVelocity *= MAXVELOCITY;

	glm::vec3 steer;
	steer.x = desiredVelocity.x - agentVelocity->vx;
	steer.y = desiredVelocity.y - agentVelocity->vy;

	agentVelocity->vx += steer.x * dt;
	agentVelocity->vy += steer.y * dt;

	if (magnitude > MAXVELOCITY)
	{
		glm::vec3 normalized = { agentVelocity->vx, agentVelocity->vy, 0 };

		double mag = glm::length(normalized);

		normalized /= mag;

		agentVelocity->vx = normalized.x * MAXVELOCITY;
		agentVelocity->vy = normalized.y * MAXVELOCITY;
	}
}

