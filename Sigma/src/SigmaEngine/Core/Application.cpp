
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

		m_Renderer->setClearColor(0.f, 0.f, 0.f, 1.f);
		while (!m_Window->shouldClose())
		{
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
		m_Renderer->clear();

		const Shader* shader = m_Renderer->shader();
		shader->setUniformMat4f("u_MVP", glm::mat4(1));
		shader->setUniform4f("u_Color", 0.f, 1.f, 0.f, 1.f);

		m_Renderer->drawRect(m_Window->getWidth() / 2-50, m_Window->getHeight() / 2-50, 100, 100);
		OnDraw();
	}
}


