#pragma once
#include "pch.h"

class PositionedOrientedObject
{

public:
	PositionedOrientedObject();
	~PositionedOrientedObject();

	glm::mat4x4				GetTransform();
	glm::vec3				GetScale();
	glm::vec3				GetPosition();
	glm::quat				GetQuaternion();

	glm::vec3				GetForward();
	glm::vec3				GetRight();
	glm::vec3				GetUp();


	void					SetQuaternion(glm::quat quat);
	void					SetPosition(glm::vec3 position);
	void					SetScale(glm::vec3 scale);

	static glm::quat		RotateWithRadianAngles(glm::mat4x4 input, glm::vec3 angles);

protected:
	virtual void			SetupMatrices();

private:

	glm::vec3				position;
	glm::vec3				scale;
	glm::mat4x4				transform;
	glm::quat				quaternion;
};

