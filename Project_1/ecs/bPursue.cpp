#include "bPursue.h"
#include "../globalStuff.h"

#include <assert.h>

PursueBehaviour::PursueBehaviour(Entity* agent, Entity* target) : mAgent(agent), mTarget(target)
{
}

PursueBehaviour::~PursueBehaviour(void)
{
}

bool LineIntersectingCircle(glm::vec3& lineOfSight, glm::vec3& lineOfSightHalf, Entity* bullet)
{	
	Transform* bulletTransform = bullet->GetComponent<Transform>();

	bool isCollideA = glm::length(bulletTransform->position - lineOfSight) < bulletTransform->sphereRadius;
	std::cout << "COLLIDE A " << glm::length(bulletTransform->position - lineOfSight) << std::endl;
//	std::cout << "COLLIDE A " << isCollideA << std::endl;

	bool isCollideB = glm::length(bulletTransform->position - lineOfSightHalf) < bulletTransform->sphereRadius;
//	std::cout << "COLLIDE B " << isCollideB << std::endl;
	std::cout << "COLLIDE B " << glm::length(bulletTransform->position - lineOfSightHalf) << std::endl;

	return (isCollideA || isCollideB);
}

bool ObstacleDetection(std::vector<Entity*>& bullets, glm::vec3& lineOfSight, glm::vec3& lineOfSightHalf, glm::vec3& threatPos, glm::vec3 agentPos)
{
	bool bIsThereAThreat = false;
	for (Entity* e : bullets)
	{
		bool bIsCollision = LineIntersectingCircle(lineOfSight, lineOfSightHalf, e);

		std::cout << bIsCollision << std::endl;

		Transform* bulletTransform = e->GetComponent<Transform>();
		glm::vec3 bulletPos = bulletTransform->position;

	//	std::cout << "a pos " << agentPos.x << " b pos " << bulletPos.x << std::endl;

		float distanceAB = glm::length(agentPos - bulletPos);

		float distanceAT = glm::length(agentPos - threatPos);

	//	std::cout << "distanceAB = " << distanceAB << " distanceAT " << distanceAT << std::endl;

		if(bIsCollision && ((threatPos == glm::vec3(0.0, 0.0, 0.0) || distanceAB < distanceAT)))
		{
			std::cout << "THERE IS A THREAT" << std::endl;
			threatPos = bulletPos;
			bIsThereAThreat = true;
		}
	}

	return bIsThereAThreat;
}

void PursueBehaviour::Update(float dt)
{
	assert(mAgent);
	assert(mTarget);

	// Gets nessesary components from entites
	Transform* agentTransform = mAgent->GetComponent<Transform>();
	Transform* targetTransform = mTarget->GetComponent<Transform>();
	Velocity* agentVelocity = mAgent->GetComponent<Velocity>();
	Velocity* targetVelocity = mTarget->GetComponent<Velocity>();
	Properties* agentProperties = mAgent->GetComponent<Properties>();

	if (agentTransform == 0 || targetTransform == 0 || agentVelocity == 0) return;

	float magnitude = glm::length(targetTransform->position - agentTransform->position);

	int T = (int)magnitude / (int)MAXVELOCITY;

	glm::vec3 futurePosition;
	futurePosition.x = targetTransform->position.x + targetVelocity->vx * T;
	futurePosition.y = targetTransform->position.y + targetVelocity->vy * T;

	glm::vec3 desiredVelocity = glm::normalize(futurePosition - agentTransform->position);

	desiredVelocity *= MAXVELOCITY;

	glm::vec3 agentVel = glm::vec3(agentVelocity->vx, agentVelocity->vy, 0);

	glm::vec3 lineOfSight = agentTransform->position + glm::normalize(agentVel) * LINEOFSIGHTRANGE;

	glm::vec3 lineOfSightHalf = agentTransform->position + glm::normalize(agentVel) * LINEOFSIGHTRANGE * 0.5f;

	glm::vec3 threatPos = glm::vec3(0.0, 0.0, 0.0);

	bool bIsThreatDetected = ObstacleDetection(g_bullets, lineOfSight, lineOfSightHalf, threatPos, agentTransform->position);
	//bool bIsThreatDetected = ObstacleDetection(g_bullets, agentTransform->position, threatPos);

	glm::vec3 steer;

	if (bIsThreatDetected)
	{
		agentProperties->setDiffuseColour(glm::vec3(1.0f, 1.0f, 0.0f));
		steer = lineOfSight - threatPos;
		steer = glm::normalize(steer);
		steer *= MAXVELOCITY;
	}
	else
	{
		agentProperties->setDiffuseColour(glm::vec3(0.0f, 1.0f, 0.0f));
		steer.x = desiredVelocity.x - agentVelocity->vx;
		steer.y = desiredVelocity.y - agentVelocity->vy;
	}

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

