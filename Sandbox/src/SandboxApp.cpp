#include <sigma.h>
#include <imgui.h>
#include <stb_image.h>

class SandboxApp : public SigmaEngine::Application
{
public:
	int m_W, m_H, m_NumChannels;

	std::unique_ptr<SigmaEngine::Texture> m_Tex;
	glm::vec4 borderColor;

	void OnStart() override {
		m_Tex = std::make_unique<SigmaEngine::Texture>("Assets/Images/SlopeChan.png");
	}

	void OnDraw() override {
		const Shader* basicShader = m_Renderer->builtInShaders().get("basic.shader");
		const Shader* texShader = m_Renderer->builtInShaders().get("basicTex.shader");
		basicShader->setUniformMat4f("u_MVP", glm::mat4(1));
		basicShader->setUniform4f("u_Color", 0.f, 1.f, 0.f, 1.0f);
		texShader->setUniformMat4f("u_MVP", glm::mat4(1));
		texShader->setUniform4f("u_Color", 0.5f, 0.5f, 0.5f, 0.5f);

		m_Tex->bind();
		texShader->setUniform1i("u_Tex", 0);

		//m_Renderer->drawRect(m_Window->getWidth() / 2 - 50, m_Window->getHeight() / 2 - 50, 100, 100);
		m_Renderer->drawTexture(*m_Tex, m_Window->getWidth() / 2, m_Window->getHeight() / 2);
	}

	void OnImGuiDraw() override {
		ImGui::Begin("Debug Menu.");
		ImGui::Text("Here's some text lol.");
		ImGui::End();
	}

	void OnQuit() override {
	}
};

SigmaEngine::Application* SigmaEngine::CreateApplication() {
	return new SandboxApp();
}