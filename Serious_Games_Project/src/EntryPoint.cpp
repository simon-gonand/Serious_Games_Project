#include "Engine/Logger.h"
#include "TrainingScreen.h"

int main() {
	Engine::Logger::Init();

	TrainingScreen* sandbox = new TrainingScreen();
	sandbox->Run();
	return 0;
}