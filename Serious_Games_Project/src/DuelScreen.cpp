#include "DuelScreen.h"

DuelScreen::DuelScreen() {
	this->setEventHandling();
	MousePoints::instance().initialise();
	ModelsResources::Initialise();

	gui_PlayerLoose = false;
	gui_PlayerHit = false;
	gui_WizardHit = false;
	gui_NotDraw = false;

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

	m_Player = new Wizard();
	m_Enemy = new Wizard();
}

DuelScreen::~DuelScreen(){
	this->removeEventHandling();
}

void DuelScreen::Run() {
	while (!glfwWindowShouldClose(m_Window->GetWindow())) {
		// clear the screen and set the background color to grey
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (m_Model == nullptr) {
			std::map<const char*, float*> models = ModelsResources::GetModels();
			auto it = models.begin();
			srand(time(NULL));
			int randomIndex = (rand() % models.size());
			std::advance(it, randomIndex);

			Engine::Shader* modelShader = new Engine::Shader("src/Shaders/Model.vert", "src/Shaders/Model.frag");
			m_Model = std::make_unique<Engine::Model>(it->second, ModelsResources::GetModelIndices()[randomIndex], 
				ModelsResources::GetModelSize(randomIndex), ModelsResources::GetModelIndicesSize(randomIndex), 
				modelShader, false, ModelsResources::GetModelReleaseNb()[randomIndex]);
			m_Entities.push_back(*m_Model);
		}

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
	ImGui::Begin("Player buttons", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
	ImFont* currentFont = ImGui::GetFont();
	currentFont->Scale = 1.3;
	ImGui::PushFont(currentFont);
	if (ImGui::Button("Finish")) {
		if (!MousePoints::instance().IsEmpty()) {
			MousePoints::instance().PopBackReleaseIndex(); // Does not count the last mouse release
			bool validMousePoints = MousePoints::instance().IsInside(*m_Model);
			Engine::Logger::GetAppLogger()->debug(validMousePoints);
			if (validMousePoints) {
				m_Model.reset(nullptr);
				m_Entities.pop_back();
				m_Enemy->ReduceLife(20);
				gui_PlayerHit = true;
				gui_WizardHit = false;
				Engine::Logger::GetAppLogger()->info("You have {} HP", m_Player->GetLife());
				Engine::Logger::GetAppLogger()->info("Your opponent has {} HP", m_Enemy->GetLife());
				if (m_Enemy->GetLife() <= 0) {
					ImGui::OpenPopup("Play Again?");
				}
			}
			else {
				m_Player->ReduceLife(20);
				gui_WizardHit = true;
				gui_PlayerHit = false;
				Engine::Logger::GetAppLogger()->info("You have {} HP", m_Player->GetLife());
				Engine::Logger::GetAppLogger()->info("Your opponent has {} HP", m_Enemy->GetLife());
				if (m_Player->GetLife() <= 0) {
					gui_PlayerLoose = true;
					ImGui::OpenPopup("Play Again?");
				}
			}
			MousePoints::instance().Clear();
		}
		else
			gui_NotDraw = MousePoints::instance().IsEmpty() ? true : false;
	}
	if (ImGui::BeginPopupModal("Play Again?", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove)) {
		if (gui_PlayerLoose) {
			ImGui::Text("You have been beaten by the wizard");
			ImGui::Text("Do you want to try again ?");
		}
		else {
			ImGui::Text("You beat the wizard");
			ImGui::Text("Do you want to play again ?");
		}
		if (ImGui::Button("Yes")) {
			if (gui_PlayerLoose) {
				delete m_Enemy;
				m_Enemy = new Wizard();
			}
			else
				m_Enemy->ResetLife();
			m_Player->ResetLife();
			ImGui::CloseCurrentPopup();
			MousePoints::instance().Clear();
		}
		ImGui::SameLine();
		if (ImGui::Button("No")) {
			MousePoints::instance().Clear();
			delete this;
			TrainingScreen* trainingScreen = new TrainingScreen();
			trainingScreen->Run();
			ImGui::CloseCurrentPopup();
			return;
		}
		ImGui::EndPopup();
	}
	if (ImGui::Button("Quit")) {
		MousePoints::instance().Clear();
		delete this;
		TrainingScreen* trainingScreen = new TrainingScreen();
		trainingScreen->Run();
		return;
	}
	ImGui::PopFont();
	ImGui::End();

	if (gui_PlayerHit || gui_WizardHit || gui_NotDraw) {
		ImGui::SetNextWindowPos(ImVec2(m_Window->GetWidth() * 0.5f, m_Window->GetHeight() * 0.1f), 
			ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::Begin(" ", nullptr,
			ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
		ImGui::PushFont(currentFont);
		if (gui_PlayerHit)
			ImGui::Text("Yes ! You hit your opponent and he lost 20 HP");
		else if (gui_WizardHit)
			ImGui::Text("Ouch ! You lost 20 HP");
		else if (gui_NotDraw)
			ImGui::Text("You didn't draw anything !");
		ImGui::PopFont();
		ImGui::End();
	}
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