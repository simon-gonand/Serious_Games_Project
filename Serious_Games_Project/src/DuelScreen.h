#pragma once

#include "Engine/WindowManager.h"
#include "Engine/StateHandling.h"
#include "Engine/Entity.h"

#include <vector>

class DuelScreen : public Engine::WindowManager, public Engine::StateHandling
{
public:
	DuelScreen();
	virtual ~DuelScreen();

	void Run();
	void GUIRender();

	//virtual void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) override;
	//virtual void MouseCallback(GLFWwindow* window, double xpos, double ypos) override;

private:
	std::vector<Engine::Entity> m_Entities;
};

