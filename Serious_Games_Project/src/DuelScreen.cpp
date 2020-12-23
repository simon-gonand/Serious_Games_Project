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

		Engine::GUI::CreateNewFrame();

		if (m_Model == nullptr) {
			std::map<const char*, float*> models = ModelsResources::GetModels();
			auto it = models.begin();
			srand(time(NULL));
			int randomIndex = (rand() % models.size());
			std::advance(it, randomIndex);

			m_ModelOnScreen = it->first;

			Engine::Shader* modelShader = new Engine::Shader("src/Shaders/Model.vert", "src/Shaders/Model.frag");
			m_Model = std::make_unique<Engine::Model>(it->second, ModelsResources::GetModelIndices()[randomIndex], 
				ModelsResources::GetModelSize(randomIndex), ModelsResources::GetModelIndicesSize(randomIndex), 
				modelShader, false, ModelsResources::GetModelReleaseNb()[randomIndex]);
		}

		for (unsigned i = 0; i < m_Entities.size(); ++i) {
				m_Entities[i].Draw();
		}
		m_Model->Draw();

		MousePoints::instance().Display();
		displayLife(m_Player->GetLife(), m_Enemy->GetLife());

		GUIRender();

		Engine::GUI::Render();

		m_Window->OnUpdate();
		if (m_Model != nullptr)
			m_Model->ReduceOpacity();
	}
}

void DuelScreen::displayLife(float playerHealth, float enemyHealth) {
	playerHealth /= 400;
	enemyHealth /= 400;
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(-0.9f, 0.82f);
	glVertex2f(-0.9f, 0.9f);
	glVertex2f(playerHealth - 0.9f, 0.9f);
	glVertex2f(playerHealth - 0.9f, 0.82f);

	glColor3f(1, 0, 0);
	glVertex2f(0.7f, 0.82f);
	glVertex2f(0.7f, 0.9f);
	glVertex2f(enemyHealth + 0.7f, 0.9f);
	glVertex2f(enemyHealth + 0.7f, 0.82f);
	glEnd();
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
			if (validMousePoints) {
				m_Model.reset(nullptr);
				m_Enemy->ReduceLife(20);
				gui_PlayerHit = true;
				gui_WizardHit = false;
				if (m_Enemy->GetLife() <= 0) {
					ImGui::OpenPopup("Play Again?");
				}
			}
			else {
				m_Player->ReduceLife(20);
				m_Model->ResetOpacity();
				gui_WizardHit = true;
				gui_PlayerHit = false;
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
			gui_PlayerLoose = false;
			gui_PlayerHit = false;
			gui_WizardHit = false;
			gui_NotDraw = false;
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

	currentFont->Scale = 1.8f;
	ImGui::Begin("PlayerLife", nullptr, 
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoMove);
	ImGui::PushFont(currentFont);
	ImGui::Text("Your Life");
	ImGui::PopFont();
	ImGui::End();

	ImGui::Begin("EnemyLife", nullptr,
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoMove);
	ImGui::PushFont(currentFont);
	ImGui::Text("Enemy's Life");
	ImGui::PopFont();
	ImGui::End();

	displayMessageOnScreen(m_ModelOnScreen);
	if (gui_PlayerHit || gui_WizardHit || gui_NotDraw) {
		if (gui_PlayerHit)
			displayMessageOnScreen("Yes ! You hit your opponent and he lost 20 HP");
		else if (gui_WizardHit)
			displayMessageOnScreen("Ouch ! You lost 20 HP");
		else if (gui_NotDraw)
			displayMessageOnScreen("You didn't draw anything !");
		
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