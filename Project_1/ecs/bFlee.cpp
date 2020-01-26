#include "bFlee.h"

#include <assert.h>

#include "../globalStuff.h"

FleeBehaviour::FleeBehaviour(Entity* agent, Entity* target) : mAgent(agent), mTarget(target)
{
}

FleeBehaviour::~FleeBehaviour(void)
{
}

void FleeBehaviour::Update(float dt)
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
	//	gBehaviourManager.SetBehaviour(mAgent, new SeekBehaviour(mAgent, mTarget));
	//	return;
	//}

	glm::vec3 desiredVelocity = glm::normalize(agentTransform->position - targetTransform->position);

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
