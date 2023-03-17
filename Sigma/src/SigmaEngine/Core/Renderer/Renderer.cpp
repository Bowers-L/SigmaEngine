#include "Renderer.h"

#include "SigmaEngine/Core/Log.h"
#include "SigmaEngine/Util/GLDebug.h"

#include <glm/glm.hpp>

namespace SigmaEngine {

	Renderer::Renderer(int width, int height) :
		m_Width(width), m_Height(height), //m_BuiltInShaders(std::filesystem::path("..") / "Sigma" / "Assets" / "Shaders", { "basic.shader" })
		m_BuiltInShaders(std::filesystem::path("Assets") / "Shaders", {"basic.shader", "basicTex.shader"})
	{
	}

	Renderer::~Renderer() {
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

	//void Renderer::setShader(const Shader& shader) {
	//	m_Shader = &shader;
	//}

	//const Shader* Renderer::shader() {
	//	return m_Shader;
	//}

	ShaderList& Renderer::builtInShaders() {
		return m_BuiltInShaders;
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

		const Shader& shader = *m_BuiltInShaders.get("basic.shader");
		draw(vao, ibo, shader);
		//const Shader& shader = *m_BuiltInShaders.get("basicTex.shader");
		//draw(vao, ibo, shader);
	}

	void Renderer::drawTexture(const Texture& tex, int x, int y) {
		const float normX = pixelToNormX(x);
		const float normY = pixelToNormY(y);
		const float normXPlusWidth = pixelToNormX(x + tex.width());
		const float normYPlusHeight = pixelToNormY(y + tex.height());

		//DEBUG_LOG("PIXEL POINTS: %d, %d, %d, %d", x, y, w, h);
		//DEBUG_LOG("POINTS: %f, %f, %f, %f", nx, ny, nxw, nyh);
		float vertices[] = {	normX, normY, 						0.f, 0.f,
								normXPlusWidth, normY,				1.f, 0.f,
								normXPlusWidth, normYPlusHeight,	1.f, 1.f,
								normX, normYPlusHeight,				0.f, 1.f,
		};

		unsigned int indices[] = { 0, 1, 2,
									2, 3, 1 };

		//Create vertex array with data
		VertexArray vao;
		VertexBuffer vbo(vertices, 4 * (2+2) * sizeof(GL_FLOAT), GL_STATIC_DRAW);
		VertexBufferLayout vbLayout;
		vbLayout.push<float>(2);
		vbLayout.push<float>(2);
		vao.addBuffer(vbo, vbLayout);

		//Create Index Buffer
		IndexBuffer ibo(indices, 6, GL_STATIC_DRAW);

		//Get the texture shader and set uniforms
		const Shader& shader = *m_BuiltInShaders.get("basicTex.shader");

		tex.bind();
		draw(vao, ibo, shader);
		tex.unbind();
	}

	//void Renderer::draw(const VertexArray& va, const IndexBuffer& ib) {
	//	draw(va, ib, *(m_Shader));
	//}

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