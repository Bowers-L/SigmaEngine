
#include "Application.h"
#include "Log.h"

#include "SigmaEngine/Events/ApplicationEvent.h"
#include "SigmaEngine/Util/GLDebug.h"

#include <string.h>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

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
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			Update();
			Draw();
			ImGuiDraw();

			m_Window->drawFrame();
		}

		OnQuit();
		Shutdown();

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
		OnDraw();
	}

	void Application::ImGuiDraw() {
		OnImGuiDraw();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Application::Shutdown() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		m_Window->close();
	}
}


