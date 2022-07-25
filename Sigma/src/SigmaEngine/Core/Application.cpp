
#include "Application.h"
#include "Log.h"

#include "SigmaEngine/Events/ApplicationEvent.h"

using namespace SigmaEngine::Events;


namespace SigmaEngine {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(800, 600);
		SIGMA_TRACE(e.ToString());
		while (true);
	}
}


