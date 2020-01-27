#include "bSeek.h"
#include "bFlee.h"
#include "../globalStuff.h"

#include <assert.h>


SeekBehaviour::SeekBehaviour(Entity* agent, Entity* target): mAgent(agent), mTarget(target)
{
}

SeekBehaviour::~SeekBehaviour(void)
{
}

void SeekBehaviour::Update(float dt)
{
	assert(mAgent);
	assert(mTarget);

	// Gets nessesary components from entites
	Transform* agentTransform = mAgent->GetComponent<Transform>();
	Transform* targetTransform = mTarget->GetComponent<Transform>();
	Velocity* agentVelocity = mAgent->GetComponent<Velocity>();

	if (agentTransform == 0 || targetTransform == 0 || agentVelocity == 0) return;

	//if (mTarget IS LOOKING AT mAgent)
	//{
	//	gBehaviourManager.SetBehaviour(mAgent, new FleeBehaviour(mAgent, mTarget));
	//	return;
	//}

	glm::vec3 desiredVelocity = glm::normalize(targetTransform->position - agentTransform->position);

	float magnitude = glm::length(targetTransform->position - agentTransform->position);

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

