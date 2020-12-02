#pragma once

// GLFW added
#include <GLFW\glfw3.h>
#include <queue>

// https://stackoverflow.com/questions/21799746/how-to-glfwsetkeycallback-for-different-classes
namespace Engine {
	class StateHandling
	{

	public:
		// Those function are optional for now, no need to instantiate all of them 
		virtual void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{};

		// optional 
		virtual void MouseCallback(GLFWwindow* window, double xpos, double ypos)
		{};

		virtual void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
		{};

		// optional
		virtual void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
		{};

		static StateHandling* event_handling_instance;
		// now cannot be overwritten as it should not be

		// should be called on demos which wish to subscribe to input
		void setEventHandling() { event_handling_instance = this; }
		// should be called at the end of every demo
		void removeEventHandling() { event_handling_instance = nullptr; }

		// __cdecl as opposed to the deprecated GLFWCALL and its __stdcall wrapped function
		static void __cdecl KeyCallback_dispatch(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (event_handling_instance)
			{
				event_handling_instance->KeyCallback(window, key, scancode, action, mods);
			}
		}

		static void __cdecl MouseButtonCallback_dispatch(GLFWwindow* window, int button, int action, int mods)
		{
			if (event_handling_instance)
			{
				event_handling_instance->MouseButtonCallback(window, button, action, mods);
			}
		}

		static void __cdecl MouseCallback_dispatch(GLFWwindow* window, double xpos, double ypos)
		{
			if (event_handling_instance)
			{
				event_handling_instance->MouseCallback(window, xpos, ypos);
			}
		}

		static void __cdecl ScrollCallback_dispatch(GLFWwindow* window, double xoffset, double yoffset)
		{
			if (event_handling_instance)
			{
				event_handling_instance->ScrollCallback(window, xoffset, yoffset);
			}
		}
	};
}