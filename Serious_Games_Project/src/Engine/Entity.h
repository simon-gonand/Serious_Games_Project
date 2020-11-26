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

		std::vector<std::vector<GLfloat>> GetVertices() const;
	
		std::vector<unsigned int> GetIndices() const;
		int GetIndexSize() const;

	private:
		Shader* m_Shader;
		std::vector<std::vector<GLfloat>> m_Vertices;
		int m_IndexSize;
		std::vector<unsigned int> m_Indices;
		unsigned int m_VAO, m_VBO, m_IBO;
		int m_VertexSize;
	};
}

