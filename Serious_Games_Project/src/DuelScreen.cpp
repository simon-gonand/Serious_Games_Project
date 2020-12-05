#include "DuelScreen.h"

DuelScreen::DuelScreen() {
	this->setEventHandling();
	MousePoints::instance().initialise();

	GLfloat backgroundVertices[4 * 5]{
		// Positions			 // Textures
	  -1.0f, -1.0f, 0.0f,		 0.0f, 0.0f, // Bottom left
	   1.0f, 1.0f, 0.0f,		 1.0f, 1.0f, // Top right
	  -1.0f, 1.0f, 0.0f,		 0.0f, 1.0f, // Top left
	   1.0f, -1.0f, 0.0f,		 1.0f, 0.0f  // Bottom right
	};

	unsigned int rectangleIndices[6] = { 0, 1, 2, 0, 1, 3 };

	Engine::Shader* backgroundShader =
		new Engine::Shader("src/Shaders/Background.vert", "src/Shaders/Background.frag", "res/DuelRoomBackground.jpg");

	std::unique_ptr<Engine::Entity> backgroundEntity =
		std::make_unique<Engine::Entity>(backgroundVertices, rectangleIndices, sizeof(backgroundVertices),
			sizeof(rectangleIndices), backgroundShader, true);
	m_Entities.push_back(*backgroundEntity);
}

DuelScreen::~DuelScreen(){
	this->removeEventHandling();
	Engine::GUI::Destroy();
}

void DuelScreen::Run() {
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

void DuelScreen::GUIRender(){
	ImGui::Begin("Player buttons");
	if (ImGui::Button("Finish")) {
		if (!MousePoints::instance().IsEmpty()) {
			MousePoints::instance().PopBackReleaseIndex(); // Does not count the last mouse release
			Engine::Logger::GetAppLogger()->info(MousePoints::instance().IsInside(*m_Model));
		}
		else
			Engine::Logger::GetAppLogger()->info("You didn't draw anything");
	}
	ImGui::End();
}

// Events
void DuelScreen::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		MousePoints::instance().SetMouseButtonIsPressed(true);
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		MousePoints::instance().SetMouseButtonIsPressed(false);
		if (m_Model != nullptr)
			MousePoints::instance().AddReleaseIndex();
	}
}

void DuelScreen::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
	if (MousePoints::instance().GetMouseButtonIsPressed()) {
		std::vector<GLfloat> pos(3);
		double xpos, ypos;
		glfwGetCursorPos(m_Window->GetWindow(), &xpos, &ypos);
		pos[0] = xpos / 480 - 1;
		pos[1] = (ypos / 270 - 1) * -1;
		pos[2] = 0.0f;
		MousePoints::instance().AddMousePoint(pos);
	}
}