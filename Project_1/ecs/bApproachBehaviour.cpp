#include "bApproachBehaviour.h"

#include <assert.h>

#include "cTransform.h"
#include "cVelocity.h"

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

	Transform* agentTransform = mAgent->GetComponent<Transform>();
	Transform* targetTransform = mTarget->GetComponent<Transform>();
	Velocity* agentVelocity = mAgent->GetComponent<Velocity>();
	Velocity* targetVelocity = mTarget->GetComponent<Velocity>();

	if (agentTransform == 0 || targetTransform == 0 || agentVelocity == 0) return;
	
	//if ((targetTransform->position.x + 150.0f < agentTransform->position.x) || (targetTransform->position.x - 150.0f > agentTransform->position.x) ||
	//	(targetTransform->position.y + 150.f < agentTransform->position.y) || (targetTransform->position.y - 150.0f > agentTransform->position.y)) 
	//{
	// Pursue direction
	glm::vec3 pursue = glm::normalize(targetTransform->position - agentTransform->position);

	// Implement the pursue code here...
	glm::quat orientation = glm::quat(glm::lookAt(agentTransform->position, pursue, UP));

	// Update agent's orientation...
	agentTransform->orientation = orientation;

	// Update the agent's velocity
	agentVelocity->vx = pursue.x;
	agentVelocity->vy = pursue.y;
	//}
}

