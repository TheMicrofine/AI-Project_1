#include "bSeekBehaviour.h"

#include <assert.h>

#include "cTransform.h"
#include "cVelocity.h"

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

	Transform* agentTransform = mAgent->GetComponent<Transform>();
	Transform* targetTransform = mTarget->GetComponent<Transform>();
	Velocity* agentVelocity = mAgent->GetComponent<Velocity>();

	if (agentTransform == 0 || targetTransform == 0 || agentVelocity == 0) return;

	// Current direction
	glm::vec3 agentForward = agentTransform->orientation * glm::vec3(0.0f, 0.0f, 1.0f);


	//glm::vec3 targetForward = targetTransform->orientation * glm::vec3(0.0f, 0.0f, 1.0f);

	//float result = glm::dot(agentForward, targetForward);

		//Results
		//Case #1: -1
		//Vectors are opposite of each other
		//Case #2: 1
		//Vectors are identical
		//Case #3: 0
		//Vectors are perpendicular
		//Case #4: > 0
		//Facing away
		//Case #5: 0 < &< 1
		//Facing towards same plane


	// seek direction
	glm::vec3 seek = glm::normalize(targetTransform->position - agentTransform->position);

	// Implement the seek code here...
	glm::quat orientation = glm::quat(glm::lookAt(agentTransform->position, seek, UP));

	// Update agent's orientation...
	agentTransform->orientation = orientation;

	// Update the agent's velocity
	agentVelocity->vx = seek.x;
	agentVelocity->vy = seek.y;
}

