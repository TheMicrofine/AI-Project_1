#include "bWander.h"
#include "../globalStuff.h"

#include <assert.h>

bool isWander = true;
bool isIdle = false;

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
	Properties* agentProperties = mAgent->GetComponent<Properties>();

	if (agentTransform == 0 || agentVelocity == 0) return;

	double currentTime = glfwGetTime();


	if (isWander)
	{
			std::cout << "wandering" << std::endl;
			//startTime = currentTime;

			agentProperties->setDiffuseColour(glm::vec3(0.0f, 1.0f, 1.0f));

			float xRand = rand() % 470 + (-470);
			float yRand = rand() % 470 + (-470);
			glm::vec3 newPosition = (glm::vec3(xRand, yRand, 0.0f));

			// Pursue direction
			glm::vec3 pursue = glm::normalize(newPosition - agentTransform->position);

			// Implement the pursue code here...
			glm::quat orientation = glm::quat(glm::lookAt(agentTransform->position, pursue, UP));

			// Update agent's orientation...
			agentTransform->orientation = orientation;

			// Update the agent's velocity
			agentVelocity->vx = pursue.x * 1.2f;
			agentVelocity->vy = pursue.y * 1.2f;

		if (currentTime - startTime >= 6.0)
		{
			startTime = currentTime;

			isWander = false;
			isIdle = true;
		}

	}

	if (isIdle)
	{
			std::cout << "Idleing" << std::endl;
			agentProperties->setDiffuseColour(glm::vec3(150.0f / 255.0f, 92.0f / 255.0f, 26.0f / 255.0f));

			agentVelocity->vx = 0.0f;
			agentVelocity->vy = 0.0f;

		if (currentTime - startTime >= 3.0)
		{
			startTime = currentTime;

			isWander = true;
			isIdle = false;
		}
	}

}

