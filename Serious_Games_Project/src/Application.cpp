#include "Application.h"

Application::Application() {
	Engine::WindowProps props = Engine::WindowProps("Window", 960, 540);
	m_Window = std::unique_ptr<Engine::Window> (Engine::Window::Create(props));

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	GLfloat vertices[4 * 5]{
		  // Positions			 // Textures
		-1.0f, -1.0f, 0.0f,		-1.0f, -1.0f,
		 1.0f, 1.0f, 0.0f,		 1.0f, 1.0f,
		-1.0f, 1.0f, 0.0f,		-1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f,		 1.0f, -1.0f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);

	// Texture coord
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	unsigned int indices[6] = { 0, 1, 2, 0, 1, 3 };
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	m_Shader = std::make_shared<Engine::Shader>("src/Shaders/Background.vert", "src/Shaders/Background.frag", "res/background.jpg");
}

Application::~Application() {
		
}

void Application::Run() {
	while (m_Running) {
		// clear the screen and set the background color to grey
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_Shader->Bind();

		glBindTexture(GL_TEXTURE_2D, m_Shader->GetTexID());
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		m_Window->OnUpdate();
	}
}