#pragma once

// Include glew
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <string>
#include <iostream>

#include "StateHandling.h"

namespace Engine {

	struct WindowProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Window",
			size_t width = 960,
			size_t height = 540)
			: Title(title), Width(width), Height(height) {}
	};

	class Window
	{
	public:
		Window(const WindowProps& props);
		~Window();

		void OnUpdate();

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;
		GLFWwindow* GetWindow() const;

	private:
		GLFWwindow* m_Window;

		struct Data {
			std::string Title;
			unsigned int Width, Height;
		};

		Data m_Data;
	};
}

