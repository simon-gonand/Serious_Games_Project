#include "Application.h"

namespace Engine {

	Application::Application() {
		WindowProps props = WindowProps("Window", 960, 540);
		m_Window = std::unique_ptr<Window> (Window::Create(props));
	}

	Application::~Application() {
		
	}

	void Application::Run() {
		while (m_Running) {
			m_Window->OnUpdate();
		}
	}
}