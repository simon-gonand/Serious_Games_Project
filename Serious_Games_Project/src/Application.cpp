#include "Application.h"

Application::Application() {
	Engine::WindowProps props = Engine::WindowProps("Window", 960, 540);
	m_Window = std::unique_ptr<Engine::Window> (Engine::Window::Create(props));
	this->setEventHandling();
	MousePoints::instance().initialise();
	m_DrawIsEnable = false;
	
	//GUI
	Engine::GUI::Init(m_Window.get());

	GLfloat backgroundVertices[4 * 5]{
		  // Positions			 // Textures
		-1.0f, -1.0f, 0.0f,		 0.0f, 0.0f, // Bottom left
		 1.0f, 1.0f, 0.0f,		 1.0f, 1.0f, // Top right
		-1.0f, 1.0f, 0.0f,		 0.0f, 1.0f, // Top left
		 1.0f, -1.0f, 0.0f,		 1.0f, 0.0f  // Bottom right
	};

	unsigned int backgroundIndices[6] = { 0, 1, 2, 0, 1, 3 };

	Engine::Shader* backgroundShader = 
		new Engine::Shader("src/Shaders/Background.vert", "src/Shaders/Background.frag", "res/background.jpg");

	std::unique_ptr<Engine::Entity> backgroundEntity = 
		std::make_unique<Engine::Entity> (backgroundVertices, backgroundIndices, sizeof(backgroundVertices),
			sizeof(backgroundIndices), backgroundShader, true);
	m_Entities.push_back(*backgroundEntity);
}

Application::~Application() {
	this->removeEventHandling();
	Engine::GUI::Destroy();
	m_Window.reset(nullptr);
}

void Application::GUIRender() {
	ImGui::Begin("Test");
	if (ImGui::Button("Clear Screen")) {
		MousePoints::instance().Clear();
		for (unsigned i = 1; i < m_Entities.size(); ++i) {
			m_Entities.erase(m_Entities.begin() + i);
			m_Models.clear();
		}
	}
	if (ImGui::Button("Display Rectangle Model")) {
		if (m_Models.find("Rectangle") == m_Models.end()) {
			GLfloat rectangleVertices[4 * 3]{
				0.0f, 0.0f, 0.0f,	// Bottom left
				0.3f, 0.1f, 0.0f,	// Top right
				0.0f, 0.1f, 0.0f,	// Top left
				0.3f, 0.0f, 0.0f,	// Bottom right
			};

			unsigned int rectangleIndices[6] = { 0, 2, 1, 1, 3, 0 };

			Engine::Shader* modelShader = new Engine::Shader("src/Shaders/Model.vert", "src/Shaders/Model.frag");
			std::unique_ptr<Engine::Entity> rectangleModelEntity =
				std::make_unique<Engine::Entity>(rectangleVertices, rectangleIndices, sizeof(rectangleVertices),
					sizeof(rectangleIndices), modelShader, false);
			m_Entities.push_back(*rectangleModelEntity);
			m_Models.insert(std::pair<const char*, Engine::Entity>("Rectangle", *rectangleModelEntity));
		}
	}
	if (ImGui::Button("Display Triangle Model")) {
		if (m_Models.find("Triangle") == m_Models.end()) {
			GLfloat triangleVertices[3 * 3]{
				-0.4f,  0.2f, 0.0f,
				-0.1f,  0.2f, 0.0f,
				-0.25f, 0.0f, 0.0f
			};

			unsigned int triangleIndices[3] = { 0, 1, 2 };

			Engine::Shader* modelShader = new Engine::Shader("src/Shaders/Model.vert", "src/Shaders/Model.frag");
			std::unique_ptr<Engine::Entity> triangleModelEntity =
				std::make_unique<Engine::Entity>(triangleVertices, triangleIndices, sizeof(triangleVertices),
					sizeof(triangleIndices), modelShader, false);
			m_Entities.push_back(*triangleModelEntity);
			m_Models.insert(std::pair<const char*, Engine::Entity>("Triangle", *triangleModelEntity));
		}
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

		MousePoints& instance = MousePoints::instance();
		for (unsigned i = 0; i < m_Entities.size(); ++i) {
			m_Entities[i].Draw();
			if (i != 0 && !instance.IsEmpty())
				std::cout << instance.IsInside(m_Entities[i]) << std::endl;
		}
		instance.Display();

		GUIRender();

		Engine::GUI::Render();

		m_Window->OnUpdate();
	}
}

// Events
void Application::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		MousePoints::instance().SetMouseButtonIsPressed(true);
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		MousePoints::instance().SetMouseButtonIsPressed(false);
		MousePoints::instance().AddReleaseIndex();
	}
}

void Application::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
	if (MousePoints::instance().GetMouseButtonIsPressed() && m_DrawIsEnable) {
		std::vector<GLfloat> pos(3);
		double xpos, ypos;
		glfwGetCursorPos(m_Window->GetWindow(), &xpos, &ypos);
		pos[0] = xpos / 480 - 1;
		pos[1] = (ypos / 270 - 1) * -1;
		pos[2] = 0.0f;
		MousePoints::instance().AddMousePoint(pos);
	}
}