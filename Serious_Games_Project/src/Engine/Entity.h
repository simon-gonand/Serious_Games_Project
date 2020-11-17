#pragma once

#include "Shader.h"

#include <memory>
#include <iostream>

namespace Engine {
	class Entity
	{
	public:
		Entity(GLfloat* vertices, unsigned int* indices, size_t vertexSize, size_t indexSize,
			Shader* shader, bool m_IsTextured);
		~Entity();

		void Draw();

	private:
		Shader* m_Shader;
		unsigned int m_VAO, m_VBO, m_IBO;
		int m_IndexSize;
	};
}

