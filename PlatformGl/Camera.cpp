#include "Camera.h"
#include "iostream"

Camera::Camera(short width, short height) :
	isPerspective(true),
	fieldOfView(45.f),
	nearDistance(0.1f),
	farDistance(100.f)
{
	this->width = width;
	this->height = height;
	ComputeViewMatrix();
	ComputeProjectionMatrix();
}

void Camera::Update(GLFWwindow* window)
{
	static double lastX = 0, lastY = 0;
	static float rotX = 0.f, rotY = 0.f;
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	double deltaX = x - lastX;
	double deltaY = y - lastY;
	lastX = x;
	lastY = y;

	auto targetY = (float)(deltaY / 50);
	auto targetX = (float)deltaX / 50;

	auto forward = GetForward();
	auto right = GetRight();
	auto rotation = glm::degrees(glm::eulerAngles(GetQuaternion()));

	//std::cout << forward.x << " " << forward.y << " " << forward.z << std::endl;
	//std::cout << forward.x << " " << forward.y << " " << forward.z << std::endl;
	std::cout << rotation.x << " " << rotation.y << " " << rotation.z << std::endl;

	forward.z = -forward.z;
	right.z = -right.z;
	auto pos = GetPosition();

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		SetPosition(pos + (forward / 10.f));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		SetPosition(pos - (forward / 10.f));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		SetPosition(pos - (right / 10.f));
	}
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		SetPosition(pos + (right / 10.f));
	}

	rotY -= targetY;
	rotX -= targetX;
	rotY = glm::clamp<float>(rotY, -85, 85);

	auto q = glm::angleAxis(glm::radians(rotX), glm::vec3(0.f, 1.f, 0.f));
	SetQuaternion(q);

}

void Camera::Setup()
{
}

void Camera::SetupMatrices()
{
	PositionedOrientedObject::SetupMatrices();
	ComputeViewMatrix();
}

void Camera::ComputeViewMatrix()
{
	viewMatrix = glm::mat4(RotateWithRadianAngles(glm::mat4(1.f), -glm::degrees(glm::eulerAngles(GetQuaternion()))));
	viewMatrix = glm::translate(viewMatrix, -GetPosition());
}

void Camera::ComputeProjectionMatrix()
{
	if (isPerspective)
	{
		projectionMatrix = glm::perspective(glm::radians(fieldOfView), 1.f * width / height, nearDistance, farDistance);
	}
	else
	{
		projectionMatrix = glm::ortho(0.f, (float)width, 0.f, (float)height, nearDistance, farDistance);
	}
}

glm::mat4x4 Camera::GetViewMatrix()
{
	return this->viewMatrix;
}

glm::mat4x4 Camera::GetProjectionMatrix()
{
	return this->projectionMatrix;
}

void Camera::SetViewPortSize(short width, short height, bool shouldCompute = true)
{
	this->width = width;
	this->height = height;
	if (shouldCompute)
		ComputeProjectionMatrix();
}

void Camera::SetPerspective(bool prs, bool shouldCompute = true)
{
	this->isPerspective = prs;
	if (shouldCompute)
		ComputeProjectionMatrix();
}

void Camera::SetFieldOfView(float fov, bool shouldCompute = true)
{
	this->fieldOfView = fov;
	if (shouldCompute)
		ComputeProjectionMatrix();
}

void Camera::SetNearDistance(float near, bool shouldCompute = true)
{
	this->nearDistance = near;
	if (shouldCompute)
		ComputeProjectionMatrix();
}

void Camera::SetFarDistance(float far, bool shouldCompute = true)
{
	this->farDistance = far;
	if (shouldCompute)
		ComputeProjectionMatrix();
}

bool Camera::IsPerspective()
{
	return isPerspective;
}

void Camera::GetViewPortSize(short* width, short* height)
{
	width = &this->width;
	height = &this->height;
}

float Camera::GetFieldOfView()
{
	return this->fieldOfView;
}

float Camera::GetNearDistance()
{
	return this->nearDistance;
}

float Camera::GetFarDistance()
{
	return this->farDistance;
}


