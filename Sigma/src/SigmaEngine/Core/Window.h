#pragma once

#include "Core.h"

#include <string>

extern class GLFWwindow;

namespace SigmaEngine {
	class SIGMA_API Window {
	private:
		GLFWwindow* m_Window;
	public:
		Window();
		~Window();

		bool init(std::string name);
		void update();
		void close();
		bool shouldClose();
	};
}