#pragma once

#ifdef SIGMA_PLATFORM_WINDOWS

extern SigmaEngine::Application* SigmaEngine::CreateApplication();

int main(int argc, char** argv) {
	SigmaEngine::Log::Init();
	SIGMA_CORE_INFO("Initialized Log!");
	//SIGMA_WARN("Hello!");
	//SIGMA_ERROR("This is a test of logging an error! Everything broken?? OH NO HOI");
	SigmaEngine::Application* app = SigmaEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif