#include "bWander.h"
#include "../globalStuff.h"

#include <assert.h>


WanderBehaviour::WanderBehaviour(Entity* agent) : mAgent(agent)
{
}

WanderBehaviour::~WanderBehaviour(void)
{
}

void WanderBehaviour::Update(float dt)
{
	assert(mAgent);

	Transform* agentTransform = mAgent->GetComponent<Transform>();
	Velocity* agentVelocity = mAgent->GetComponent<Velocity>();

	if (agentTransform == 0 || agentVelocity == 0) return;

	double currentTime = glfwGetTime();

	if (currentTime - startTime > 3)
	{
		startTime = currentTime;

		float xRand = rand() % 515 + (-1160);
		float yRand = rand() % 630 + (-115);
		glm::vec3 newPosition = (glm::vec3(xRand, yRand, 0.0f));

		// Pursue direction
		glm::vec3 pursue = glm::normalize(newPosition - agentTransform->position);

		// Implement the pursue code here...
		glm::quat orientation = glm::quat(glm::lookAt(agentTransform->position, pursue, UP));

		// Update agent's orientation...
		agentTransform->orientation = orientation;

		// Update the agent's velocity
		agentVelocity->vx = pursue.x;
		agentVelocity->vy = pursue.y;
	}
}

