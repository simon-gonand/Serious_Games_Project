#pragma once

#include "Shader.h"

#include <memory>
#include <iostream>

namespace Engine {
	class Entity
	{
	public:
		Entity(GLfloat* vertices, unsigned int* indices, size_t vertexSize, size_t indexSize,
			Shader* shader, bool isTextured);
		~Entity();

		void Draw();

		std::vector<std::vector<GLfloat>> GetVertices() const;
	
		std::vector<unsigned int> GetIndices() const;
		int GetIndexSize() const;

	protected: 
		Shader* m_Shader;
		unsigned int m_VAO;
		int m_IndexSize;

	private:
		std::vector<std::vector<GLfloat>> m_Vertices;
		std::vector<unsigned int> m_Indices;
		unsigned int m_VBO, m_IBO;
		int m_VertexSize;
	};
}

