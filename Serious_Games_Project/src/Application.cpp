#include "Application.h"

Application::Application() {
	Engine::WindowProps props = Engine::WindowProps("Window", 960, 540);
	m_Window = std::unique_ptr<Engine::Window> (Engine::Window::Create(props));
}

Application::~Application() {
		
}

void Application::Run() {
	while (m_Running) {
		// clear the screen and set the background color to grey
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_Window->OnUpdate();
	}
}