#pragma once

#include "System.h"

namespace Engine {

	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}

