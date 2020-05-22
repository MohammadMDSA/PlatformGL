#include "PositionedOrientedObject.h"

PositionedOrientedObject::PositionedOrientedObject() :
	position(glm::vec3(0.f)),
	scale(glm::vec3(1.f)),
	transform(glm::mat4(1.f)),
	quaternion(glm::quatLookAt(glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f)))
{
	SetupMatrices();
}

PositionedOrientedObject::~PositionedOrientedObject()
{
}

glm::mat4x4 PositionedOrientedObject::GetTransform()
{
	return this->transform;
}

glm::vec3 PositionedOrientedObject::GetScale()
{
	return this->scale;
}

glm::vec3 PositionedOrientedObject::GetPosition()
{
	return this->position;
}

glm::quat PositionedOrientedObject::GetQuaternion()
{
	return quaternion;
}

glm::vec3 PositionedOrientedObject::GetForward()
{
	auto res4 = glm::vec4(0.f, 0.f, 1.f, 0) * quaternion;
	return glm::vec3(res4);
}

glm::vec3 PositionedOrientedObject::GetRight()
{
	auto res4 = glm::vec4(1.f, 0.f, 0.f, 0) * quaternion;
	return glm::vec3(res4);
}

glm::vec3 PositionedOrientedObject::GetUp()
{
	auto res4 = glm::vec4(0.f, 1.f, 0.f, 0) * quaternion;
	return glm::vec3(res4);
}

void PositionedOrientedObject::SetQuaternion(glm::quat quat)
{
	this->quaternion = quat;
	SetupMatrices();
}

void PositionedOrientedObject::SetPosition(glm::vec3 position)
{
	this->position = position;
	SetupMatrices();

}

void PositionedOrientedObject::SetScale(glm::vec3 scale)
{
	this->scale = scale;
	SetupMatrices();

}

glm::quat PositionedOrientedObject::RotateWithRadianAngles(glm::mat4x4 input, glm::vec3 angles)
{
	
	return glm::quat(glm::radians(angles));

}

void PositionedOrientedObject::SetupMatrices()
{
	this->transform = glm::mat4(1.f);
	this->transform = glm::translate(transform, position);
	this->transform = transform * glm::mat4(quaternion);
	this->transform = glm::scale(transform, scale);

}