#include "Application.h"
#include <stdio.h>

namespace Engine {

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		printf("Hello World!");
		while (true);
	}
}