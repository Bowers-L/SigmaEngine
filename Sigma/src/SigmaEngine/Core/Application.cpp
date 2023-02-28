
#include "Application.h"
#include "Log.h"

#include "SigmaEngine/Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

using namespace SigmaEngine::Events;


namespace SigmaEngine {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	int Application::Run()
	{
		WindowResizeEvent e(800, 600);
		SIGMA_TRACE(e.ToString());

        GLFWwindow* window;

        /* Initialize the library */
        if (!glfwInit())
            return -1;

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
	}
}


