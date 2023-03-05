#pragma once

#include "Core.h"

#include <string>

extern class GLFWwindow;

namespace SigmaEngine {

	struct WindowProps
	{
		std::string title;
		unsigned int width, height;

		WindowProps(const std::string& title = "Sigma",
			uint32_t width = 800,
			uint32_t height = 600)
		: title(title), width(width), height(height)
		{}
	};

	class SIGMA_API Window {
	private:
		GLFWwindow* m_Window;
		WindowProps m_Props;

		Window(const WindowProps& props = WindowProps());
	public:
		static Window* create(const WindowProps& props = WindowProps());

		~Window();

		uint32_t getWidth() const;
		uint32_t getHeight() const;

		void drawFrame();
		void close();
		bool shouldClose();
	private:
		void init(const WindowProps& props = WindowProps());
	};
}