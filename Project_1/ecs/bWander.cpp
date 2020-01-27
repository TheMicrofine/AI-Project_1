#include "bWander.h"
#include "cTransform.h"
#include "cVelocity.h"
#include <iostream>
#include <math.h>

#define PI 3.14159265358979323846

#include <assert.h>

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
