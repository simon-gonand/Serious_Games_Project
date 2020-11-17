#include "Entity.h"

namespace Engine {
	Entity::Entity(GLfloat* vertices, unsigned int* indices, size_t vertexSize, size_t indexSize,
		Shader* shader, bool isTextured, int drawType) {
		
		glGenVertexArrays(1, &this->m_VAO);
		glBindVertexArray(this->m_VAO);

		glGenBuffers(1, &this->m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
		glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

		m_IndexSize = indexSize;
		glGenBuffers(1, &this->m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndexSize, indices, GL_STATIC_DRAW);

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
}