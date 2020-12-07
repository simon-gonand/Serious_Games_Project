#include "TrainingScreen.h"

TrainingScreen::TrainingScreen() {
	this->setEventHandling();
	MousePoints::instance().initialise();
	m_DrawIsEnable = false;

	GLfloat backgroundVertices[4 * 5]{
		  // Positions			 // Textures
		-1.0f, -1.0f, 0.0f,		 0.0f, 0.0f, // Bottom left
		 1.0f, 1.0f, 0.0f,		 1.0f, 1.0f, // Top right
		-1.0f, 1.0f, 0.0f,		 0.0f, 1.0f, // Top left
		 1.0f, -1.0f, 0.0f,		 1.0f, 0.0f  // Bottom right
	};

	unsigned int backgroundIndices[6] = { 0, 1, 2, 0, 1, 3 };

	Engine::Shader* backgroundShader = 
		new Engine::Shader("src/Shaders/Background.vert", "src/Shaders/Background.frag", "res/ClassRoomBackground.jpg");

	std::unique_ptr<Engine::Entity> backgroundEntity = 
		std::make_unique<Engine::Entity> (backgroundVertices, backgroundIndices, sizeof(backgroundVertices),
			sizeof(backgroundIndices), backgroundShader, true);
	m_Entities.push_back(*backgroundEntity);
}

TrainingScreen::~TrainingScreen() {
	this->removeEventHandling();
}

void TrainingScreen::GUIRender() {
	ImGui::Begin("Manage on screen");
	if (ImGui::Button("Clear Screen")) {
		MousePoints::instance().Clear();
		for (unsigned i = 1; i < m_Entities.size(); ++i) {
			m_Entities.erase(m_Entities.begin() + i);
			m_Model.reset();
		}
	}
	if (ImGui::Button("Display Rectangle Model")) {
		if (m_Model == nullptr) {
			GLfloat rectangleVertices[4 * 3]{
				0.0f, 0.0f, 0.0f,	// Bottom left
				0.3f, 0.1f, 0.0f,	// Top right
				0.0f, 0.1f, 0.0f,	// Top left
				0.3f, 0.0f, 0.0f,	// Bottom right
			};

			unsigned int rectangleIndices[6] = { 0, 2, 1, 1, 3, 0 };

			Engine::Shader* modelShader = new Engine::Shader("src/Shaders/Model.vert", "src/Shaders/Model.frag");
			m_Model = std::make_unique<Engine::Model>(rectangleVertices, rectangleIndices, sizeof(rectangleVertices),
					sizeof(rectangleIndices), modelShader, false, 0);
			m_Entities.push_back(*m_Model);
		}
	}
	if (ImGui::Button("Display Triangle Model")) {
		if (m_Model == nullptr) {
			GLfloat triangleVertices[3 * 3]{
				-0.4f,  0.2f, 0.0f,
				-0.1f,  0.2f, 0.0f,
				-0.25f, 0.0f, 0.0f
			};

			unsigned int triangleIndices[3] = { 0, 1, 2 };

			Engine::Shader* modelShader = new Engine::Shader("src/Shaders/Model.vert", "src/Shaders/Model.frag");
			m_Model = std::make_unique<Engine::Model>(triangleVertices, triangleIndices, sizeof(triangleVertices),
					sizeof(triangleIndices), modelShader, false, 0);
			m_Entities.push_back(*m_Model);
		}
	}
	if (ImGui::Button("Duel Screen")) {
		MousePoints::instance().Clear();
		delete this;
		DuelScreen* duelScreen = new DuelScreen();
		duelScreen->Run();
		return;
	}
	ImGui::Checkbox("Enable Draw", &m_DrawIsEnable);
	ImGui::End();
	ImGui::Begin("Player buttons");
	if (ImGui::Button("Finish")) {
		MousePoints::instance().PopBackReleaseIndex(); // Does not count the last mouse release
		if (!MousePoints::instance().IsEmpty() && m_Model != nullptr) {
			Engine::Logger::GetAppLogger()->info(MousePoints::instance().IsInside(*m_Model));
		}
		else if (m_Model == nullptr)
			Engine::Logger::GetAppLogger()->info("There's no model on the screen");
		else
			Engine::Logger::GetAppLogger()->info("You didn't draw anything");
	}
	ImGui::End();
}

void TrainingScreen::Run() {
	while (!glfwWindowShouldClose(m_Window->GetWindow())) {
		// clear the screen and set the background color to grey
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Engine::GUI::CreateNewFrame();

		for (unsigned i = 0; i < m_Entities.size(); ++i) {
			m_Entities[i].Draw();
		}

		MousePoints::instance().Display();

		GUIRender();

		Engine::GUI::Render();

		m_Window->OnUpdate();
	}
}

// Events
void TrainingScreen::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		MousePoints::instance().SetMouseButtonIsPressed(true);
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		MousePoints::instance().SetMouseButtonIsPressed(false);
		if (m_DrawIsEnable && m_Model != nullptr)
			MousePoints::instance().AddReleaseIndex();
	}
}

void TrainingScreen::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
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