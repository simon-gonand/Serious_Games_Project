#include "Model.h"

namespace Engine {
	Model::Model(GLfloat* vertices, unsigned int* indices, size_t vertexSize, size_t indexSize,
		Shader* shader, bool isTextured, int numberOfReleasePossible)
		: Entity(vertices, indices, vertexSize, indexSize, shader, isTextured),
		m_NumberOfReleasePossible(numberOfReleasePossible)
	{
	}

	Model::~Model(){}

	int Model::GetNumberOfReleasePossible() const { return m_NumberOfReleasePossible; }
}