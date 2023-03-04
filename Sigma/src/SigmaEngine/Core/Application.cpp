
#include "Application.h"
#include "Log.h"

#include "SigmaEngine/Events/ApplicationEvent.h"
#include "SigmaEngine/Util/GLDebug.h"

#include <string.h>

using namespace SigmaEngine::Events;

namespace SigmaEngine {
	Application::Application()
	{
		m_Window = Window::create();
		m_Renderer = Renderer::create(m_Window->getWidth(), m_Window->getHeight());
	}

	Application::~Application()
	{
		delete m_Window;
		delete m_Renderer;
	}

	int Application::Run()
	{
		const bool startupSuccess = Startup();
		SG_CORE_ASSERT(startupSuccess, "Could not startup application.");

		while (!m_Window->shouldClose())
		{
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

			Update();
			Draw();

			m_Window->update();
		}

		OnQuit();
		m_Window->close();

		return 0;
	}

	bool Application::Startup()
	{
		OnStart();
		return true;
	}

	void Application::Update()
	{
		OnUpdate();
	}

	void Application::Draw()
	{
		m_Renderer->drawRect(0, 0, 100, 100);
		OnDraw();
	}
}


