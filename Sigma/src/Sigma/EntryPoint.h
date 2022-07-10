#pragma once

#ifdef SIGMA_PLATFORM_WINDOWS

extern Sigma::Application* Sigma::CreateApplication();

int main(int argc, char** argv) {
	Sigma::Log::Init();
	SIGMA_CORE_INFO("Initialized Log!");
	SIGMA_WARN("Hello!");
	SIGMA_ERROR("WTF EVERYTHING BROKEN?? OH NO HOI");
	Sigma::Application* app = Sigma::CreateApplication();
	app->Run();
	delete app;
}

#endif