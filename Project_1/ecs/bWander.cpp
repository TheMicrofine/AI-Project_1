#include "bWander.h"
#include "cTransform.h"
#include "cVelocity.h"
#include <iostream>
#include <math.h>

#define PI 3.14159265358979323846

#include <assert.h>
//bool isWander = true;
//bool isIdle = false;

WanderBehaviour::WanderBehaviour(Entity* agent) : mAgent(agent)
{
	isWandering = false;
	isIdling = false;
	xPosition = 0;
	yPosition = 0;
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

	//std::cout << "Desired Position before: " << xPosition << " " << yPosition << std::endl;

	if (isWandering == false && isIdling == false)
	{
		//float xPosition = rand() % 515 + (-1160);
		//float yPosition = rand() % 630 + (-115);
		
		float xPosition = 0;
		float yPosition = 0;





		//float circleRadius = 15.0f;

		//glm::vec3 circlePoint = glm::normalize(glm::vec3(agentVelocity->vx, agentVelocity->vy, 0));

		//float angle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (PI * 2)));

		//float x = sin(angle) * circleRadius;
		//float y = cos(angle) * circleRadius;

		//xPosition = circlePoint.x + x;
		//yPosition = circlePoint.y + y;

		isWandering = true;
	}
	
	// if (isWander)
	// {
			// std::cout << "wandering" << std::endl;
			// //startTime = currentTime;

			// agentProperties->setDiffuseColour(glm::vec3(0.0f, 1.0f, 1.0f));

			// float xRand = rand() % 470 + (-470);
			// float yRand = rand() % 470 + (-470);
			// glm::vec3 newPosition = (glm::vec3(xRand, yRand, 0.0f));

			// // Pursue direction
			// glm::vec3 pursue = glm::normalize(newPosition - agentTransform->position);

			// // Implement the pursue code here...
			// glm::quat orientation = glm::quat(glm::lookAt(agentTransform->position, pursue, UP));

			// // Update agent's orientation...
			// agentTransform->orientation = orientation;

			// // Update the agent's velocity
			// agentVelocity->vx = pursue.x * 1.2f;
			// agentVelocity->vy = pursue.y * 1.2f;

		// if (currentTime - startTime >= 6.0)
		// {
			// startTime = currentTime;

			// isWander = false;
			// isIdle = true;
		// }

	// }

	// if (isIdle)
	// {
			// std::cout << "Idleing" << std::endl;
			// agentProperties->setDiffuseColour(glm::vec3(150.0f / 255.0f, 92.0f / 255.0f, 26.0f / 255.0f));

			// agentVelocity->vx = 0.0f;
			// agentVelocity->vy = 0.0f;

		// if (currentTime - startTime >= 3.0)
		// {
			// startTime = currentTime;

			// isWander = true;
			// isIdle = false;
		// }
	// }

// }

	glm::vec3 desiredPosition = { xPosition, yPosition, 0 };

	//std::cout << "Desired Position after: " << xPosition << " " << yPosition << std::endl;

	glm::vec3 desiredVelocity = glm::normalize(desiredPosition - agentTransform->position);

	float magnitude = glm::length(desiredPosition - agentTransform->position);

	if (magnitude < 0.5)
	{
		// STALL FOR 3 SECONDS
		isWandering = false;
		isIdling = true;

		//if (HAS BEEN WAITING FOR 3 SECONDS)
		//{
		//	isWandering = false;
		//}
	}
	
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
