#pragma once

#include "SigmaEngine/Core/Log.h"

#include "buffers/Buffers.h"
#include "Shader.h"
#include "Texture.h"

#include <unordered_map>
#include <filesystem>

namespace SigmaEngine {
	struct ShaderList {
		const std::filesystem::path m_RelativeDir;
		const std::vector<std::string> m_ShaderNames;

		std::unordered_map<std::string, std::unique_ptr<Shader>> m_Shaders;

		ShaderList(const std::filesystem::path relativeDir, const std::vector<std::string> shaderNames) 
		: m_RelativeDir(relativeDir), m_ShaderNames(shaderNames) {
			init();
		}

		~ShaderList() {
		}

		void init() {
			for (auto& name : m_ShaderNames) {
				std::filesystem::path shaderFilepath = std::filesystem::current_path() / m_RelativeDir / name;
				SG_CORE_INFO("Making Shader: {}", shaderFilepath.string());
				m_Shaders[name] = std::make_unique<Shader>(shaderFilepath.string());
			}
		}

		const Shader* get(const std::string shaderName) {
			if (m_Shaders.find(shaderName) == m_Shaders.end()) {
				SG_CORE_ERROR("Could not find shader: {}", shaderName);
			}

			return m_Shaders[shaderName].get();
		}
	};

	//Renderer is a singleton
	class Renderer {
	private:
		ShaderList m_BuiltInShaders;
		int m_Width, m_Height;

		Renderer(int windowWidth, int windowHeight);
	public:
		Renderer(Renderer& other) = delete;
		void operator=(const Renderer&) = delete;

		~Renderer();

		static Renderer* create(int width, int height);

		//OpenGL Coords are normalized btw -1 and 1, so we need to have a way to normalize pixel coordinates on the screen
		float pixelToNormX(int x);
		float pixelToNormY(int y);

		void clear();
		void setClearColor(float r, float g, float b, float a);

		ShaderList& builtInShaders();
		//const Shader* shader();
		//void setShader(const Shader& shader);

		void drawRect(int x, int y, int width, int height);
		void drawTexture(const Texture& tex, int x, int y);
		//void draw(const VertexArray& va, const IndexBuffer& ib);
		void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	};
}