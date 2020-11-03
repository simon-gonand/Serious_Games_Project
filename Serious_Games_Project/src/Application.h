#pragma once

#include "Engine/Window.h"
#include "Engine/Shader.h"
#include "Engine/GUI.h"
#include "Engine/StateHandling.h"

#include <memory>

class Application: public StateHandling
{
public:
	Application();
	virtual ~Application();

	void Run();
	void GUIRender();

	virtual void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) override;

private:
	std::unique_ptr<Engine::Window> m_Window;

	unsigned int m_VAO, m_VBO, m_IBO;

	std::shared_ptr<Engine::Shader> m_Shader;

	bool m_MouseButtonIsPressed;
};

