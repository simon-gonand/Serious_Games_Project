#pragma once

#include "Engine/Window.h"

#include <memory>

class Application
{
public:
	Application();
	virtual ~Application();

	void Run();

private:
	std::unique_ptr<Engine::Window> m_Window;
	bool m_Running = true;
};

