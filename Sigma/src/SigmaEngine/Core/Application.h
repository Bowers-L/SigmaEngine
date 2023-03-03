#pragma once

#include "Core.h"

#include "Window.h"
#include "Renderer/Renderer.h"

namespace SigmaEngine {
	class SIGMA_API Application
	{
	private:
		Window* m_Window;
		Renderer* m_Renderer;
	public:
		Application();
		virtual ~Application();

		int Run();
	};

	Application* CreateApplication();	//Define in Client
}