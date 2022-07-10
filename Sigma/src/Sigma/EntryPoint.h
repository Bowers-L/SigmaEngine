#pragma once

#ifdef SIGMA_PLATFORM_WINDOWS

extern Sigma::Application* Sigma::CreateApplication();

int main(int argc, char** argv) {
	printf("Welcome to the Sigma Engine!");
	Sigma::Application* app = Sigma::CreateApplication();
	app->Run();
	delete app;
}

#endif