#include "Renderer.h"

#include "SigmaEngine/Core/Log.h"
#include "SigmaEngine/Util/GLDebug.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

Renderer* Renderer::s_Instance = nullptr;

Renderer::Renderer(int width, int height) :
m_Width(width), m_Height(height), m_Shader(nullptr)
{
	if (s_Instance == nullptr) {
		s_Instance = this;
	}
	else {
		SIGMA_WARN("Renderer is a singleton, but there was an attempt to construct it twice.");
	}
}

void Renderer::CreateInstance(int width, int height) {
	s_Instance = new Renderer(width, height);
}

float Renderer::pixelToNormX(int x)
{
	return (float) x / s_Instance->m_Width * 2 - 1;
}

float Renderer::pixelToNormY(int y)
{
	return -( (float) y / s_Instance->m_Height * 2 - 1);
}

void Renderer::setShader(const Shader& shader) {
	s_Instance->m_Shader = &shader;
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
	if (s_Instance->m_Shader == nullptr) {
		SIGMA_ERROR("Renderer must have shader set.");
		return;
	}

	float normX = pixelToNormX(x);
	float normY = pixelToNormY(y);
	float normXPlusWidth = pixelToNormX(x + width);
	float normYPlusHeight = pixelToNormY(y + height);

	//DEBUG_LOG("PIXEL POINTS: %d, %d, %d, %d", x, y, w, h);
	//DEBUG_LOG("POINTS: %f, %f, %f, %f", nx, ny, nxw, nyh);
	float vertices[] = {	normX, normY, 0.0f,
							normXPlusWidth, normY, 0.0f,
							normX, normYPlusHeight, 0.0f,
							normXPlusWidth, normYPlusHeight, 0.0f,
	};

	unsigned int indices[] = {	0, 1, 2,
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
	if (s_Instance->m_Shader == nullptr) {
		SIGMA_ERROR("Renderer must have shader set.");
		return;
	}

	draw(va, ib, *(s_Instance->m_Shader));
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

/*
void Renderer::drawLine(glm::vec3 p1, glm::vec3 p2, float weight, const glm::vec4& color) {
	glm::vec3 normDir = glm::normalize(glm::vec3(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z));

	float positions[] = { p1.x + normDir.y * weight / 2, p1.y - normDir.x * weight / 2, p1.z,
						p1.x - normDir.y * weight / 2, p1.y + normDir.x * weight / 2, p1.z,
						p2.x + normDir.y * weight / 2, p2.y - normDir.x * weight / 2, p2.z,
						p2.x - normDir.y * weight / 2, p2.y + normDir.x * weight / 2, p2.z,
	};

	unsigned int indices[] = { 0, 1, 2,
								2, 3, 0,
	};

	VertexArray va;

	VertexBuffer vb(positions, 3 * 4 * sizeof(float), GL_STATIC_DRAW);
	VertexBufferLayout layout;
	layout.push<float>(3);
	va.addBuffer(vb, layout);

	IndexBuffer ib(indices, 6, GL_STATIC_DRAW);

	glm::mat4 mvp = glm::ortho(0, WIDTH, HEIGHT, 0, 1, -1);

	Shader shader("res/shaders/Basic.shader");
	shader.bind();
	shader.setUniformMat4f("u_MVP", mvp);
	shader.setUniform4f("u_Color", color.r, color.g, color.b, color.a);

	draw(va, ib, shader);
}
*/
