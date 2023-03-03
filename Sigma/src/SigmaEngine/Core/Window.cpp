#include "Window.h"

#include "SigmaEngine/Core/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "SigmaEngine/Util/GLDebug.h"

namespace SigmaEngine
{
    Window* SigmaEngine::Window::create(const WindowProps& props)
    {
        return new Window(props);
    }

    Window::Window(const WindowProps& props)
    {
        init(props);
    }

    Window::~Window()
    {
        close();
    }

    void Window::init(const WindowProps& props)
    {
        m_Props = props;

        /* Initialize the library */
        int glfwSuccess = glfwInit();
        SG_CORE_ASSERT(glfwSuccess, "Failed to initialize GLFW.")

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


        /* Create a windowed mode window and its OpenGL context */
        m_Window = glfwCreateWindow(props.width, props.height, props.title.c_str(), NULL, NULL);
        SG_CORE_ASSERT(m_Window != nullptr, "Failed to create GLFW window.");

        /* Make the window's context current */
        glfwMakeContextCurrent(m_Window);

        int gladSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        SG_CORE_ASSERT(gladSuccess, "Failed to initialize GLAD");

        GLCall(glViewport(0, 0, props.width, props.height));
    }

    bool Window::shouldClose()
    {
        return glfwWindowShouldClose(m_Window);
    }

    void Window::update()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(m_Window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    uint32_t Window::getWidth() const
    {
        return m_Props.width;
    }

    uint32_t Window::getHeight() const
    {
        return m_Props.height;
    }

    void Window::close()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }
}
