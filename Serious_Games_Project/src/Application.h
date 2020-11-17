#pragma once

#include "Engine/Window.h"
#include "Engine/Shader.h"
#include "Engine/GUI.h"
#include "Engine/StateHandling.h"
#include "Engine/Entity.h"

#include <memory>
#include <vector>

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

	bool m_DrawIsEnable;
	bool m_MouseButtonIsPressed;
	std::vector<std::vector<GLfloat>> m_MousePoints;
	std::vector<int> m_MouseReleaseIndices;
	void DisplayMousePoints();
};

