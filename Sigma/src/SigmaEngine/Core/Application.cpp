
#include "Application.h"
#include "Log.h"

#include "SigmaEngine/Events/ApplicationEvent.h"
//#include "SigmaEngine/Util/GLDebug.h"

#include <string.h>


using namespace SigmaEngine::Events;

namespace SigmaEngine {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	int Application::Run()
	{
		if (!m_Window.init("YOOO MR WHITE")) {
			SIGMA_CORE_ERROR("Failed to create window.");
		}

		while (!m_Window.shouldClose()) {
			m_Window.update();
		}

		m_Window.close();

		return 0;
	}
}


