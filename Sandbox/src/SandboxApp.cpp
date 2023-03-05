#include <sigma.h>
#include <imgui.h>

class SandboxApp : public SigmaEngine::Application
{
	void OnDraw() override {
		const Shader* shader = m_Renderer->shader();
		shader->setUniformMat4f("u_MVP", glm::mat4(1));
		shader->setUniform4f("u_Color", 0.f, 1.f, 0.f, 1.f);

		m_Renderer->drawRect(m_Window->getWidth() / 2 - 50, m_Window->getHeight() / 2 - 50, 100, 100);
	}

	void OnImGuiDraw() override {
		ImGui::Begin("Yo Mr. White checkout this debug window.");
		ImGui::Text("Here's some text lol.");
		ImGui::End();
	}
};

SigmaEngine::Application* SigmaEngine::CreateApplication() {
	return new SandboxApp();
}