#pragma once

#include "pch.h"

#include "PositionedOrientedObject.h"
#include "IFunctionalObject.h"

class Camera : public PositionedOrientedObject, public IFunctionalObject
{
public:
	Camera(short width, short height);
	~Camera();

	void				Update(GLFWwindow* window) override;
	void				Setup() override;

	glm::mat4x4			GetViewMatrix();
	glm::mat4x4			GetProjectionMatrix();

	void				SetViewPortSize(short width, short height, bool shouldCompute);
	void				SetPerspective(bool prs, bool shouldCompute);
	void				SetFieldOfView(float fov, bool shouldCompute);
	void				SetNearDistance(float near, bool shouldCompute);
	void				SetFarDistance(float far, bool shouldCompute);

	bool				IsPerspective();
	void				GetViewPortSize(short* width, short* height);
	float				GetFieldOfView();
	float				GetNearDistance();
	float				GetFarDistance();
	
protected:
	virtual void		SetupMatrices() override;

private:
	void				ComputeViewMatrix();
	void				ComputeProjectionMatrix();

	glm::mat4x4			projectionMatrix;
	glm::mat4x4			viewMatrix;
	bool				isPerspective;
	short				width;
	short				height;
	float				fieldOfView;
	float				nearDistance;
	float				farDistance;
};

