#include "cTransform.h"

const glm::vec3 RIGHT = glm::vec3(1.0f, 0.0f, 0.0);
const glm::vec3 UP = glm::vec3(0.0f, 1.0f, 0.0);
const glm::vec3 FORWARD = glm::vec3(0.0f, 0.0f, 1.0);

Transform::Transform()
{
	this->position = glm::vec3(0.0f);
	this->scale = glm::vec3(1.0f);
	this->orientation = glm::quat((glm::vec3(0.0f, 0.0f, 0.0f)));
}

void Transform::setUniformScale(float scale)
{
	this->scale = glm::vec3(scale, scale, scale);
}

glm::quat Transform::getQOrientation(void) 
{ 
	return this->orientation;
};
