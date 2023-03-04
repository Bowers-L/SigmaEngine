#include "Renderer.h"

#include "SigmaEngine/Core/Log.h"
#include "SigmaEngine/Util/GLDebug.h"

#include <glm/glm.hpp>

namespace SigmaEngine {

	Renderer::Renderer(int width, int height) :
		m_Width(width), m_Height(height), //m_BuiltInShaders(std::filesystem::path("..") / "Sigma" / "Assets" / "Shaders", { "basic.shader" })
		m_BuiltInShaders(std::filesystem::path("Assets") / "Shaders", {"basic.shader"})
	{
		m_Shader = m_BuiltInShaders.get("basic.shader");
	}

	Renderer::~Renderer() {
		delete m_Shader;
	}

	Renderer* Renderer::create(int width, int height) {
		Renderer* r = new Renderer(width, height);

		return r;
	}

	float Renderer::pixelToNormX(int x)
	{
		return (float)x / m_Width * 2 - 1;
	}

	float Renderer::pixelToNormY(int y)
	{
		return -((float)y / m_Height * 2 - 1);
	}

	void Renderer::setShader(const Shader& shader) {
		m_Shader = &shader;
	}

	const Shader* Renderer::shader() {
		return m_Shader;
	}

	void Renderer::clear() {
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void Renderer::setClearColor(float r, float g, float b, float a)
	{
		GLCall(glClearColor(r, g, b, a));
	}

	void Renderer::drawRect(int x, int y, int width, int height)
	{
		const float normX = pixelToNormX(x);
		const float normY = pixelToNormY(y);
		const float normXPlusWidth = pixelToNormX(x + width);
		const float normYPlusHeight = pixelToNormY(y + height);

		//DEBUG_LOG("PIXEL POINTS: %d, %d, %d, %d", x, y, w, h);
		//DEBUG_LOG("POINTS: %f, %f, %f, %f", nx, ny, nxw, nyh);
		glm::vec3 vertices[] = { glm::vec3(normX, normY, 0.0f),
								glm::vec3(normXPlusWidth, normY, 0.0f),
								glm::vec3(normX, normYPlusHeight, 0.0f),
								glm::vec3(normXPlusWidth, normYPlusHeight, 0.0f),
		};

		unsigned int indices[] = { 0, 1, 2,
									2, 3, 1 };

		//Create vertex array with data
		VertexArray vao;
		VertexBuffer vbo(vertices, 4 * 3 * sizeof(GL_FLOAT), GL_STATIC_DRAW);
		VertexBufferLayout vbLayout;
		vbLayout.push<float>(3);
		vao.addBuffer(vbo, vbLayout);

		//Create Index Buffer
		IndexBuffer ibo(indices, 6, GL_STATIC_DRAW);

		draw(vao, ibo);
	}

	void Renderer::draw(const VertexArray& va, const IndexBuffer& ib) {
		draw(va, ib, *(m_Shader));
	}

	void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader)
	{
		va.bind();
		ib.bind();
		shader.bind();

		GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));

		shader.unbind();
		ib.unbind();
		va.unbind();
	}
}