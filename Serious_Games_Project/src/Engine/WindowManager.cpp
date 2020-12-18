#include "WindowManager.h"

namespace Engine {
	std::unique_ptr<Window>WindowManager::m_Window = std::unique_ptr<Window>(new Window(Engine::WindowProps("Window", 960, 540)));

	WindowManager::WindowManager() {
		GUI::Init(m_Window.get());
	}

	WindowManager::~WindowManager(){
		GUI::Destroy();
	}

	void WindowManager::displayMessageOnScreen(const char* message) {
		ImGui::SetNextWindowPos(ImVec2(m_Window->GetWidth() * 0.5f, m_Window->GetHeight() * 0.1f),
			ImGuiCond_Always, ImVec2(0.5f, 0.5f));
		ImGui::Begin(" ", nullptr,
			ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
		ImFont* currentFont = ImGui::GetFont();
		currentFont->Scale = 1.3;
		ImGui::PushFont(currentFont);
		ImGui::Text(message);
		ImGui::PopFont();
		ImGui::End();
	}
}