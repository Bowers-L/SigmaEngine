#pragma once

#include <glad/glad.h>

#include "SigmaEngine/Core/Log.h"

#include "buffers/Buffers.h"

#include "Shader.h"

//Renderer is a singleton
class Renderer {
private:
	static Renderer* s_Instance;

	int m_Width, m_Height;
	const Shader* m_Shader;

	Renderer(int windowWidth, int windowHeight);
public :
	Renderer(Renderer& other) = delete;
	void operator=(const Renderer&) = delete;

	static void CreateInstance(int width, int height);

	//OpenGL Coords are normalized btw -1 and 1, so we need to have a way to normalize pixel coordinates on the screen
	static float pixelToNormX(int x);
	static float pixelToNormY(int y);

	static void clear();
	static void setClearColor(float r, float g, float b, float a);
	static void setShader(const Shader& shader);

	static void drawRect(int x, int y, int width, int height);	
	static void draw(const VertexArray& va, const IndexBuffer& ib);
	static void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
};