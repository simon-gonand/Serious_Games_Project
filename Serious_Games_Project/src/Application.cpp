#include "Application.h"

Application::Application() {
	Engine::WindowProps props = Engine::WindowProps("Window", 960, 540);
	m_Window = std::unique_ptr<Engine::Window> (Engine::Window::Create(props));
	this->setEventHandling();
	m_MouseButtonIsPressed = false;
	m_DrawIsEnable = false;
	
	//GUI
	Engine::GUI::Init(m_Window.get());

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	GLfloat vertices[4 * 5]{
		  // Positions			 // Textures
		-1.0f, -1.0f, 0.0f,		 0.0f, 0.0f, // Bottom left
		 1.0f, 1.0f, 0.0f,		 1.0f, 1.0f, // Top right
		-1.0f, 1.0f, 0.0f,		 0.0f, 1.0f, // Top left
		 1.0f, -1.0f, 0.0f,		 1.0f, 0.0f  // Bottom right
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);

	// Texture coord
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	unsigned int indices[6] = { 0, 1, 2, 0, 1, 3 };
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	m_Shader = std::make_shared<Engine::Shader>("src/Shaders/Background.vert", "src/Shaders/Background.frag", "res/background.jpg");
}

Application::~Application() {
	this->removeEventHandling();
	Engine::GUI::Destroy();
	m_Window.reset(nullptr);
}

void Application::GUIRender() {
	ImGui::Begin("Test");
	if (ImGui::Button("Clear Screen")) {
		m_MousePoints.clear();
		m_MouseReleaseIndices.clear();
	}
	ImGui::Checkbox("Enable Draw", &m_DrawIsEnable);
	ImGui::End();
}

void Application::Run() {
	while (!glfwWindowShouldClose(m_Window->GetWindow())) {
		// clear the screen and set the background color to grey
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Engine::GUI::CreateNewFrame();

		m_Shader->Bind();


		glBindTexture(GL_TEXTURE_2D, m_Shader->GetTexID());
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		DisplayMousePoints();

		GUIRender();

		Engine::GUI::Render();

		m_Window->OnUpdate();
	}
}

void Application::DisplayMousePoints() {
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glBegin(GL_LINES);
	for (int i = 1; i < m_MousePoints.size(); ++i) {
		glColor3f(0.0f, 0.0f, 0.0f);//The color of the painted points
		if (std::find(m_MouseReleaseIndices.begin(), m_MouseReleaseIndices.end(), i) != m_MouseReleaseIndices.end()) {
			glVertex3f(m_MousePoints[i][0], m_MousePoints[i][1], m_MousePoints[i][2]);
			if (i < m_MousePoints.size() - 1)
				glVertex3f(m_MousePoints[i + 1][0], m_MousePoints[i + 1][1], m_MousePoints[i + 1][2]);
		}
		else {
			glVertex3f(m_MousePoints[i][0], m_MousePoints[i][1], m_MousePoints[i][2]);
			glVertex3f(m_MousePoints[i - 1][0], m_MousePoints[i - 1][1], m_MousePoints[i - 1][2]);
		}
	}
	glEnd();
}

// Events
void Application::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		m_MouseButtonIsPressed = true;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		m_MouseButtonIsPressed = false;
		m_MouseReleaseIndices.push_back(m_MousePoints.size());
	}
}

void Application::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
	if (m_MouseButtonIsPressed && m_DrawIsEnable) {
		std::vector<GLfloat> pos(3);
		double xpos, ypos;
		glfwGetCursorPos(m_Window->GetWindow(), &xpos, &ypos);
		pos[0] = xpos / 480 - 1;
		pos[1] = (ypos / 270 - 1) * -1;
		pos[2] = 0.0f;
		m_MousePoints.push_back(pos);
	}
}