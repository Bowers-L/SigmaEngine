#pragma once

#include "Core.h"

#include "Window.h"
#include "Renderer/Renderer.h"

namespace SigmaEngine {
	class SIGMA_API Application
	{
	protected:
		Window* m_Window;
		Renderer* m_Renderer;
	public:
		Application();
		virtual ~Application();

		int Run();

		bool Startup();	//Called when application starts.
		void Update();
		void Draw();
		void Shutdown();
		void ImGuiDraw();

		virtual void OnStart() {}	//Called after startup
		virtual void OnUpdate() {}	//Update before drawing
		virtual void OnDraw() {}	//Render game objects
		virtual void OnImGuiDraw() {}
		virtual void OnQuit() {}	//Called right before the window closes.
	};

	Application* CreateApplication();	//Define in Client
}