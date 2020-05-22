#pragma once

#include "GraphicDevice.h"
#include "GameObject.h"


class GraphicDevice;

class CubeObject : public GameObject
{
public:
	CubeObject(GraphicDevice* device);

	void				Update(GLFWwindow* window) override;
	void				Setup() override;

};

