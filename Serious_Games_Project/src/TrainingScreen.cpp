#include "TrainingScreen.h"

TrainingScreen::TrainingScreen() {
	this->setEventHandling();
	MousePoints::instance().initialise();
	ModelsResources::Initialise();
	m_DrawIsEnable = false;

	gui_Pass = false;
	gui_NotPass = false;
	gui_NoModel = false;
	gui_NotDraw = false;

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
	ImFont* currentFont = ImGui::GetFont();
	currentFont->Scale = 1.3;
	ImGui::PushFont(currentFont);
	if (ImGui::Button("Clear Screen")) {
		MousePoints::instance().Clear();
		for (unsigned i = 1; i < m_Entities.size(); ++i) {
			m_Entities.erase(m_Entities.begin() + i);
			m_Model.reset();
		}
	}

	std::map<const char*, float*> models = ModelsResources::GetModels();
	int index = 0;
	for (std::pair<const char*, float*> itr: models) {
		std::string buttonName = "Display ";
		buttonName += itr.first;
		buttonName += " Model";
		if (ImGui::Button(buttonName.c_str())) {
			if (m_Model == nullptr) {
				m_ModelOnScreen = buttonName.c_str();
				Engine::Shader* modelShader = new Engine::Shader("src/Shaders/Model.vert", "src/Shaders/Model.frag");
				m_Model = std::make_unique<Engine::Model>(itr.second, ModelsResources::GetModelIndices()[index],
					ModelsResources::GetModelSize(index), ModelsResources::GetModelIndicesSize(index),
					modelShader, false, ModelsResources::GetModelReleaseNb()[index]);
			}
		}
		++index;
	}

	if (ImGui::Button("Duel Screen")) {
		MousePoints::instance().Clear();
		delete this;
		DuelScreen* duelScreen = new DuelScreen();
		duelScreen->Run();
		return;
	}
	ImGui::Checkbox("Enable Draw", &m_DrawIsEnable);
	ImGui::PopFont();
	ImGui::End();

	ImGui::Begin("Player buttons", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
	ImGui::PushFont(currentFont);
	if (ImGui::Button("Finish")) {
		if (!MousePoints::instance().IsEmpty() && m_Model != nullptr) {
			if (MousePoints::instance().IsInside(*m_Model)) {
				gui_Pass = true;
				gui_NotPass = false;
			}
			else {
				gui_NotPass = true;
				gui_Pass = false;
			}
			gui_NotDraw = false;
			gui_NoModel = false;
		}
		else {
			gui_NotPass = false;
			gui_Pass = false;
			gui_NotDraw = MousePoints::instance().IsEmpty() ? true : false;
			gui_NoModel = m_Model == nullptr ? true : false;
		}
		
	}
	ImGui::PopFont();
	ImGui::End();

	if (gui_Pass || gui_NotPass || gui_NoModel || gui_NotDraw) {
		if (gui_Pass)
			displayMessageOnScreen("Congratulations ! You learn a new sign !");
		else if (gui_NotPass)
			displayMessageOnScreen("Sorry ! Try again !");
		else {
			if (gui_NoModel)
				displayMessageOnScreen("There's no model on screen");
			if (gui_NotDraw)
				displayMessageOnScreen("You didn't draw anything");
		}
	}
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
		if (m_Model != nullptr)
			m_Model->Draw();
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
		if (m_DrawIsEnable) {
			MousePoints::instance().AddReleaseIndex();
		}
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