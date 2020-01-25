#include "bPursueBehaviour.h"

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

	Transform* agentTransform = mAgent->GetComponent<Transform>();
	Transform* targetTransform = mTarget->GetComponent<Transform>();
	Velocity* agentVelocity = mAgent->GetComponent<Velocity>();
	Velocity* targetVelocity = mTarget->GetComponent<Velocity>();

	if (agentTransform == 0 || targetTransform == 0 || agentVelocity == 0) return;
	
	//e.position + e.forward * e.velocity = e.future
	glm::vec3 targetforward = targetTransform->orientation * glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 future = targetTransform->position + targetforward * (glm::vec3(targetVelocity->vx, targetVelocity->vy, 0.0f));

	// Pursue direction
	glm::vec3 pursue = glm::normalize(future - agentTransform->position);

	// Implement the pursue code here...
	glm::quat orientation = glm::quat(glm::lookAt(agentTransform->position, pursue, UP));

	// Update agent's orientation...
	agentTransform->orientation = orientation;

	// Update the agent's velocity
	agentVelocity->vx = pursue.x;
	agentVelocity->vy = pursue.y;
}

