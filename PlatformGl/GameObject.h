#pragma once

#include "pch.h"

#include "GraphicDevice.h"
#include "PositionedOrientedObject.h"
#include "IFunctionalObject.h"

class GraphicDevice;

class GameObject : public PositionedOrientedObject, public IFunctionalObject
{

public:
	GameObject(GraphicDevice* device);
	~GameObject();
	void					Render();

	virtual void			Update(GLFWwindow* window) = 0;
	virtual void			Setup()	= 0;

protected:
	unsigned int			vbo;
	unsigned int			vao;
	unsigned int			ebo;
	GraphicDevice*			device;
	float*					vertices;
	unsigned int*			indices;
	unsigned int			texture;
	short					indicesSize;
	short					verticesSize;
};

