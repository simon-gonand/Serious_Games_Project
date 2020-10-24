#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char* argv[]) {
	auto sandbox = Engine::CreateApplication();
	sandbox->Run();
	delete sandbox;
	return 0;
}

#endif