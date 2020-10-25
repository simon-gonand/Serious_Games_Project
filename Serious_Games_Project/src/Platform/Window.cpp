#include "Window.h"

#include "../Engine/Logger.h"

namespace Engine {
	
	static bool GLFW_Initialized = false;

	Window::Window(const WindowProps& props) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		// Initialize the library
		if (!GLFW_Initialized) {
			if (!glfwInit()) {
				Engine::Logger::GetSystemLogger()->error("GLFW library isn't initialize");
				return;
			}
			GLFW_Initialized = true;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		m_Window = glfwCreateWindow((int) props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
		if (!m_Window)
		{
			glfwTerminate();
			Engine::Logger::GetSystemLogger()->error("Window {1} didn't create properly", props.Title);
			return ;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(m_Window);
		glfwSwapInterval(1); // sets the frame rate
		//glfwSetWindowUserPointer(m_Window, &m_Data); // To use for windows events

		Engine::Logger::GetSystemLogger()->info("Window \"{}\" Width: {}, Height: {} is set", props.Title, props.Width, props.Height);
	}

	Window::~Window() {
		glfwDestroyWindow(m_Window);
	}

	Window* Window::Create(const WindowProps& props) {
		return new Window(props);
	}

	void Window::OnUpdate() {
		/* Swap front and back buffers */
		glfwSwapBuffers(m_Window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	unsigned int Window::GetWidth() const { return m_Data.Width; }
	unsigned int Window::GetHeight() const { return m_Data.Height; }
}