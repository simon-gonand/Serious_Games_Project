#pragma once

#include "Engine/Window.h"
#include "Engine/Shader.h"
#include "Engine/GUI.h"
#include "Engine/StateHandling.h"
#include "Engine/Entity.h"
#include "MousePoints.h"

#include <memory>
#include <vector>
#include <map>

class Application: public StateHandling
{
public:
	Application();
	virtual ~Application();

	void Run();
	void GUIRender();

	virtual void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) override;
	virtual void MouseCallback(GLFWwindow* window, double xpos, double ypos) override;

private:
	std::unique_ptr<Engine::Window> m_Window;

	std::vector<Engine::Entity> m_Entities;
	std::map<const char*, Engine::Entity> m_Models;

	bool m_DrawIsEnable;
};

