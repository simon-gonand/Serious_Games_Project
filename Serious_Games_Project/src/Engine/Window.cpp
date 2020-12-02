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
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1); // if 3 glVertex doesn't work

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
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			Logger::GetAppLogger()->info("GLEW ERROR: failed initialization!");
		}

		/*glfwSetKeyCallback(m_Window, StateHandling::KeyCallback_dispatch);			    // Not useful yet
		glfwSetScrollCallback(m_Window, StateHandling::ScrollCallback_dispatch);*/
		glfwSetCursorPosCallback(m_Window, StateHandling::MouseCallback_dispatch);
		glfwSetMouseButtonCallback(m_Window, StateHandling::MouseButtonCallback_dispatch);
	}

	Window::~Window() {
		glfwDestroyWindow(m_Window);
	}

	void Window::OnUpdate() {
		/* Swap front and back buffers */
		glfwSwapBuffers(m_Window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	unsigned int Window::GetWidth() const { return m_Data.Width; }
	unsigned int Window::GetHeight() const { return m_Data.Height; }
	GLFWwindow* Window::GetWindow() const { return m_Window; }
}