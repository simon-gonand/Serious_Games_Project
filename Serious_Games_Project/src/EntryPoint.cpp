#include "Engine/Logger.h"
#include "Application.h"

int main() {
	Engine::Logger::Init();

	Application* sandbox = new Application();
	sandbox->Run();
	delete sandbox;
	return 0;
}