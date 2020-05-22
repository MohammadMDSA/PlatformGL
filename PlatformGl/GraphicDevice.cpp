#include "GraphicDevice.h"

GraphicDevice::GraphicDevice()
{
}

void GraphicDevice::SetupDevice()
{
	shader = new Shader("platform.vs", "platform.fs");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);
}

void GraphicDevice::Render(std::vector<GameObject*>* objects)
{

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->use();

	for (auto object = objects->begin(); object != objects->end(); object++)
	{
		(*object)->Render();
	}

}

Shader* GraphicDevice::GetShader()
{
	return this->shader;
}
