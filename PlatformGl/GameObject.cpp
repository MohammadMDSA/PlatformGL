#include "GameObject.h"

GameObject::GameObject(GraphicDevice* device):
	vbo(0),
	vao(0),
	ebo(0),
	vertices(nullptr),
	indices(nullptr),
	texture(0),
	indicesSize(0),
	verticesSize(0)
{
	this->device = device;
}

GameObject::~GameObject()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteTextures(1, &texture);
	delete vertices;
	delete indices;
}

void GameObject::Render()
{
	glBindTexture(GL_TEXTURE_2D, texture);
	unsigned int modelLoc = glGetUniformLocation(device->GetShader()->ID, "transform");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(this->GetTransform()));
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
}
