#include "DuelScreen.h"

DuelScreen::DuelScreen() {
	this->setEventHandling();
	MousePoints::instance().initialise();
	ModelsResources::Initialise();

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
	Engine::GUI::Destroy();
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
	ImGui::Begin("Player buttons");
	if (ImGui::Button("Finish")) {
		MousePoints::instance().PopBackReleaseIndex(); // Does not count the last mouse release
		if (!MousePoints::instance().IsEmpty()) {
			bool validMousePoints = MousePoints::instance().IsInside(*m_Model);
			Engine::Logger::GetAppLogger()->debug(validMousePoints);
			if (validMousePoints) {
				m_Model.reset(nullptr);
				m_Entities.pop_back();
				m_Enemy->ReduceLife(20);
				Engine::Logger::GetAppLogger()->info("Yes ! You hit your opponent and he lost 20 HP");
				Engine::Logger::GetAppLogger()->info("You have {} HP", m_Player->GetLife());
				Engine::Logger::GetAppLogger()->info("Your opponent has {} HP", m_Enemy->GetLife());
				if (m_Enemy->GetLife() <= 0) {
					Engine::Logger::GetAppLogger()->info("You beat the wizard");
					// Message if he wants to play another battle
					delete m_Enemy;
					m_Enemy = new Wizard();
					m_Player->ResetLife();
				}
			}
			else {
				m_Player->ReduceLife(20);
				Engine::Logger::GetAppLogger()->info("Ouch ! You lost 20 HP");
				Engine::Logger::GetAppLogger()->info("You have {} HP", m_Player->GetLife());
				Engine::Logger::GetAppLogger()->info("Your opponent has {} HP", m_Enemy->GetLife());
				if (m_Player->GetLife() <= 0) {
					Engine::Logger::GetAppLogger()->info("You have been beaten by the wizard");
					// Play again ?
					m_Enemy->ResetLife();
					m_Player->ResetLife();
				}
			}
			MousePoints::instance().Clear();
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