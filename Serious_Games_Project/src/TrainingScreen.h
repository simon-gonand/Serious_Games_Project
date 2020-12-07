#pragma once

#include "Engine/WindowManager.h"
#include "Engine/StateHandling.h"
#include "Engine/Window.h"
#include "Engine/Shader.h"
#include "Engine/GUI.h"
#include "Engine/Entity.h"
#include "Engine/Model.h"
#include "MousePoints.h"
#include "DuelScreen.h"

#include <memory>
#include <vector>
#include <map>

class TrainingScreen: public Engine::WindowManager, public Engine::StateHandling
{
public:
	TrainingScreen();
	virtual ~TrainingScreen();

	void Run();
	void GUIRender();

	virtual void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) override;
	virtual void MouseCallback(GLFWwindow* window, double xpos, double ypos) override;

private:
	std::vector<Engine::Entity> m_Entities;
	std::unique_ptr<Engine::Model> m_Model;

	bool m_DrawIsEnable;

	bool gui_Pass;
	bool gui_NotPass;
	bool gui_NotDraw;
	bool gui_NoModel;
};

