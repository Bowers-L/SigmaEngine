#pragma once

#include "Core.h"

namespace SigmaEngine {
	class SIGMA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();


	};

	Application* CreateApplication();	//Define in Client
}