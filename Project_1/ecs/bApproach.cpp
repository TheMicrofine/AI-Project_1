#include "bApproach.h"
#include "cTransform.h"
#include "cVelocity.h"

#include <assert.h>
#include <ctime>

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

	// Gets nessesary components from entites
	Transform* agentTransform = mAgent->GetComponent<Transform>();
	Transform* targetTransform = mTarget->GetComponent<Transform>();
	Velocity* agentVelocity = mAgent->GetComponent<Velocity>();

	if (agentTransform == 0 || targetTransform == 0 || agentVelocity == 0) return;

	glm::vec3 desiredVelocity = glm::normalize(targetTransform->position - agentTransform->position);

	glm::vec3 distance = targetTransform->position - agentTransform->position;

	distance.x = fabs(distance.x);
	distance.y = fabs(distance.y);

	if (distance.x < SLOWINGRADIUS && distance.y < SLOWINGRADIUS)
	{
		desiredVelocity = desiredVelocity * MAXVELOCITY * (distance / SLOWINGRADIUS);
	}
	else
	{
		desiredVelocity *= MAXVELOCITY;
	}

	glm::vec3 steer;

	if (distance.x < MAINTAINRADUIS && distance.y < MAINTAINRADUIS)
	{
		agentVelocity->vx = 0;
		agentVelocity->vy = 0;

		// shoot mans
		float currentTime = std::clock();


	}
	else
	{
		steer.x = desiredVelocity.x - agentVelocity->vx;
		steer.y = desiredVelocity.y - agentVelocity->vy;

		agentVelocity->vx += steer.x * dt;
		agentVelocity->vy += steer.y * dt;
	}

	if (agentVelocity->vx > MAXVELOCITY)
		agentVelocity->vx = MAXVELOCITY;

	if (agentVelocity->vy > MAXVELOCITY)
		agentVelocity->vy = MAXVELOCITY;

	//glm::vec3 desiredVelocity = glm::normalize(targetTransform->position - agentTransform->position);

	//float distance = glm::length(targetTransform->position - agentTransform->position);

	//std::cout << distance << std::endl;

	//if (distance < SLOWINGRADIUS)
	//{
	//	desiredVelocity = desiredVelocity * MAXVELOCITY * (distance / SLOWINGRADIUS);
	//	std::cout << "IN SLOWING RADIUS" << std::endl;
	//	std::cout << "Y VALUE" << desiredVelocity.y << std::endl;
	//}
	//else
	//{
	//	desiredVelocity *= MAXVELOCITY;
	//}

	//glm::vec3 steer;

	//std::cout << "MATH: " << (distance/MAINTAINRADUIS)<< std::endl;
	//if (distance < MAINTAINRADUIS)
	//{
	//	//agentVelocity->vx = 0;
	//	//agentVelocity->vy = 0;
	//	std::cout << "IN MAINTAIN RADIUS" << std::endl;
	//	steer.x = -agentVelocity->vx;
	//	steer.y = -agentVelocity->vy;
	//}
	//else
	//{
	//	steer.x = desiredVelocity.x - agentVelocity->vx;
	//	steer.y = desiredVelocity.y - agentVelocity->vy;
	//}

	//agentVelocity->vx += steer.x * dt;
	//agentVelocity->vy += steer.y * dt;
	//
	//if (distance > MAXVELOCITY)
	//{
	//	glm::vec3 normalized = { agentVelocity->vx, agentVelocity->vy, 0 };

	//	double mag = glm::length(normalized);

	//	normalized /= mag;

	//	agentVelocity->vx = normalized.x * MAXVELOCITY;
	//	agentVelocity->vy = normalized.y * MAXVELOCITY;
	//}
}

