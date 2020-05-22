#pragma once
#include "pch.h"

#include "GameObject.h"
#include "Shader.h"

class GameObject;

class GraphicDevice
{

public:
	GraphicDevice();

	void SetupDevice();
	void Render(std::vector<GameObject*>* objects);


	Shader* GetShader();

private:
	Shader*			shader;

};

