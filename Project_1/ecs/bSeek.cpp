#include "bSeek.h"
#include "bFlee.h"
#include "../globalStuff.h"

#include <assert.h>


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

	// Gets nessesary components from entites
	Transform* agentTransform = mAgent->GetComponent<Transform>();
	Transform* targetTransform = mTarget->GetComponent<Transform>();
	Velocity* agentVelocity = mAgent->GetComponent<Velocity>();
	Properties* agentProperties = mAgent->GetComponent<Properties>();

	if (agentTransform == 0 || targetTransform == 0 || agentVelocity == 0) return;

	glm::vec3 agentForward = agentTransform->orientation * glm::vec3(0.0f, 0.0f, 1.0f);

	glm::vec3 targetForward = targetTransform->orientation * glm::vec3(0.0f, 0.0f, 1.0f);

	float result = glm::dot(agentForward, targetForward);

	if (result == -1)
	{

	}
	else if (result == 1)
	{

	}
	else if (result == 0)
	{

	}
	else if (result > 0)
	{

	}
	else if (0 < result && result < 1)
	{

	}

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

	//if (mTarget IS LOOKING AT mAgent)
	//{
	//	gBehaviourManager.SetBehaviour(mAgent, new FleeBehaviour(mAgent, mTarget));
	//	agentProperties->setDiffuseColour(glm::vec3(0.0f, 0.0f, 1.0f));
	//	return;
	//}

	glm::vec3 desiredVelocity = glm::normalize(targetTransform->position - agentTransform->position);

	float magnitude = glm::length(targetTransform->position - agentTransform->position);

	desiredVelocity *= MAXVELOCITY;
	
	glm::vec3 steer;
	steer.x = desiredVelocity.x - agentVelocity->vx;
	steer.y = desiredVelocity.y - agentVelocity->vy;

	// glm::mat4 lookAt ( glm::vec3 eye, glm::vec3 center, glm::vec3 up )

	//glm::quat orientation = glm::quat(glm::lookAt(agentTransform->position, steer, UP));

	//glm::quat orientation = glm::quat(glm::lookAt(agentTransform->position, steer, UP));

	//orientation = glm::normalize(orientation);

	//agentTransform->orientation = orientation;

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

