#pragma once

#include "Core.h"

#include "Window.h"

namespace SigmaEngine {
	class SIGMA_API Application
	{
	private:
		Window* m_Window;
	public:
		Application();
		virtual ~Application();

		int Run();
	};

	Application* CreateApplication();	//Define in Client
}