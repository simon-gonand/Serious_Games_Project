#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char* argv[]) {
	Engine::Logger::Init();

	auto sandbox = Engine::CreateApplication();
	sandbox->Run();
	delete sandbox;
	return 0;
}

#endif