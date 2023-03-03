#pragma once

#ifdef SIGMA_PLATFORM_WINDOWS

extern SigmaEngine::Application* SigmaEngine::CreateApplication();

int main(int argc, char** argv) {
	SigmaEngine::Log::Init();
	SG_CORE_INFO("Initialized Log!");

	SigmaEngine::Application* app = SigmaEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif