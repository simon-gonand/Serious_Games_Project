#include "Model.h"

namespace Engine {
	Model::Model(GLfloat* vertices, unsigned int* indices, size_t vertexSize, size_t indexSize,
		Shader* shader, bool isTextured, int numberOfReleasePossible)
		: Entity(vertices, indices, vertexSize, indexSize, shader, isTextured),
		m_NumberOfReleasePossible(numberOfReleasePossible), m_Opacity (1.0f)
	{
	}

	Model::~Model(){}

	int Model::GetNumberOfReleasePossible() const { return m_NumberOfReleasePossible; }

	void Model::Draw() {
		Logger::GetSystemLogger()->debug(m_Opacity);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		m_Shader->Bind();
		GLint opacityLocation = glGetUniformLocation(m_Shader->GetProgram(), "opacity");
		glUniform1f(opacityLocation, m_Opacity);
		glBindVertexArray(this->m_VAO);
		glDrawElements(GL_TRIANGLES, m_IndexSize, GL_UNSIGNED_INT, 0);
		m_Shader->Unbind();
	}

	void Model::ReduceOpacity() { m_Opacity -= 0.001f; }
	void Model::ResetOpacity() { m_Opacity = 1.0f; }
}