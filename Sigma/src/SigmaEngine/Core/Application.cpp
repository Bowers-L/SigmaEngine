
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
		//m_Renderer = Renderer::create(m_Window->getWidth(), m_Window->getHeight());
	}

	Application::~Application()
	{
		delete m_Window;
		//delete m_Renderer;
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


