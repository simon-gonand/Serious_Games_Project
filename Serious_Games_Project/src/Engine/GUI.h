#pragma once

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Window.h"

namespace Engine {
	class GUI
	{
	public:
		GUI();
		~GUI();

		static void Init(Window* window);
		static void CreateNewFrame();
		static void Render();
		static void Destroy();
	};
}
