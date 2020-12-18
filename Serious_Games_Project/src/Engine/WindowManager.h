#pragma once

#include "Window.h"
#include "GUI.h"

#include <memory>

namespace Engine {
	class WindowManager
	{
	public:
		WindowManager();
		virtual ~WindowManager();

		virtual void GUIRender() {};
		virtual void Run() {};

	protected :
		static WindowProps props;
		static std::unique_ptr<Window> m_Window;

		void displayMessageOnScreen(const char* message);
	};
}

