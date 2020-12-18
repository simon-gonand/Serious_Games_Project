#pragma once

#include "Engine/WindowManager.h"
#include "Engine/StateHandling.h"
#include "Engine/Entity.h"
#include "MousePoints.h"
#include "Wizard.h"
#include "ModelsResources.h"
#include "TrainingScreen.h"

#include <vector>
#include <time.h>

class DuelScreen : public Engine::WindowManager, public Engine::StateHandling
{
public:
	DuelScreen();
	virtual ~DuelScreen();

	void Run();
	void GUIRender();

	virtual void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) override;
	virtual void MouseCallback(GLFWwindow* window, double xpos, double ypos) override;

private:
	std::vector<Engine::Entity> m_Entities;
	std::unique_ptr<Engine::Model> m_Model;
	const char* m_ModelOnScreen;

	Wizard* m_Player;
	Wizard* m_Enemy;

	bool gui_PlayerLoose;
	bool gui_PlayerHit;
	bool gui_WizardHit;
	bool gui_NotDraw;

	// Use the algorithm found here 
	// https://stackoverflow.com/questions/12655123/open-gl-filling-portion-of-quadrilateral-with-color
	void displayLife(float playerHealth, float enemyHealth);
};

