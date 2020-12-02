#include "WindowManager.h"

namespace Engine {
	std::unique_ptr<Window>WindowManager::m_Window = std::unique_ptr<Window>(new Window(Engine::WindowProps("Window", 960, 540)));

	WindowManager::WindowManager() {
		GUI::Init(m_Window.get());
	}

	WindowManager::~WindowManager(){
		GUI::Destroy();
	}
}