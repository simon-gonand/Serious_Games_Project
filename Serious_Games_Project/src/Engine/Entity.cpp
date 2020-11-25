#include "Entity.h"

namespace Engine {
	Entity::Entity(GLfloat* vertices, unsigned int* indices, size_t vertexSize, size_t indexSize,
		Shader* shader, bool isTextured, int drawType) {
		glGenVertexArrays(1, &this->m_VAO);
		glBindVertexArray(this->m_VAO);

		for (unsigned i = 0; i < vertexSize / sizeof(GLfloat); i = i + 3) {
			std::vector<GLfloat> coord;
			coord.push_back(vertices[i]);
			coord.push_back(vertices[i + 1]);
			coord.push_back(vertices[i + 2]);
			m_Vertices.push_back(coord);
		}
		glGenBuffers(1, &this->m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
		glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

		m_IndexSize = indexSize;
		for (unsigned i = 0; i < m_IndexSize / sizeof(unsigned int); ++i)
			m_Indices.push_back(indices[i]);
		glGenBuffers(1, &this->m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices, GL_STATIC_DRAW);

		if (isTextured) {
			// Position
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);

			// Texture coord
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		}
		else {
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		}

		glBindVertexArray(0);

		m_DrawType = drawType;
		m_Shader = shader;
	}

	Entity::~Entity(){}

	void Entity::Draw() {
		m_Shader->Bind();
		glBindVertexArray(this->m_VAO);
		glDrawElements(m_DrawType, m_IndexSize, GL_UNSIGNED_INT, 0);
		m_Shader->Unbind();
	}

	std::vector<std::vector<GLfloat>> Entity::GetVertices() const { return m_Vertices; }
	
	std::vector<unsigned int> Entity::GetIndices() const { 
		return m_Indices; 
	}
	int Entity::GetIndexSize() const { return m_IndexSize; }
}