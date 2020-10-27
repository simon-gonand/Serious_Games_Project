#pragma once

// Include glew
#include "GL/glew.h"

#include <string>

#include "GLFW/glfw3.h"
#include "../Engine/System.h"

namespace Engine {

	struct WindowProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Window",
			unsigned int width = 960,
			unsigned int height = 540)
			: Title(title), Width(width), Height(height) {}
	};

	class ENGINE_API Window
	{
	public:
		Window(const WindowProps& props);
		~Window();

		void OnUpdate();

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;

		static Window* Create(const WindowProps& props);

	private:
		GLFWwindow* m_Window;

		struct Data {
			std::string Title;
			unsigned int Width, Height;
		};

		Data m_Data;
	};
}

