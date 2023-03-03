
#include "Application.h"
#include "Log.h"

#include "SigmaEngine/Events/ApplicationEvent.h"
//#include "SigmaEngine/Util/GLDebug.h"

#include <string.h>


using namespace SigmaEngine::Events;

namespace SigmaEngine {
	Application::Application()
	{
		m_Window = Window::create();
	}

	Application::~Application()
	{
		delete m_Window;
	}

	int Application::Run()
	{
		while (!m_Window->shouldClose()) {
			m_Window->update();
		}

		m_Window->close();

		return 0;
	}
}


