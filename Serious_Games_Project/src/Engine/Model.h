#pragma once

#include "Entity.h"

namespace Engine {

	class Model: public Entity
	{
	private:
		int m_NumberOfReleasePossible;

	public:
		Model(GLfloat* vertices, unsigned int* indices, size_t vertexSize, size_t indexSize,
			Shader* shader, bool isTextured, int numberOfRelease);

		int GetNumberOfReleasePossible() const;
	};
}

