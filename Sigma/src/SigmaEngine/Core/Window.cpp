#include "Window.h"

#include "SigmaEngine/Core/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

SigmaEngine::Window::Window() 
{
}

SigmaEngine::Window::~Window()
{
    close();
    delete m_Window;
}

bool SigmaEngine::Window::init(std::string name) {
    /* Initialize the library */
    if (!glfwInit()) {
        SIGMA_CORE_ERROR("Failed to initialize GLFW.");
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    m_Window = glfwCreateWindow(800, 600, name.c_str(), NULL, NULL);
    if (!m_Window)
    {
        SIGMA_CORE_ERROR("Failed to create GLFW window.");
        glfwTerminate();
        return false;
    }

    //GLCall(glViewport(0, 0, 800, 600));

    /* Make the window's context current */
    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        SIGMA_CORE_ERROR("Failed to initialize glad");
        return false;
    }

    return true;
}

bool SigmaEngine::Window::shouldClose() {
    return glfwWindowShouldClose(m_Window);
}

void SigmaEngine::Window::update() {
    glClear(GL_COLOR_BUFFER_BIT);

    /* Swap front and back buffers */
    glfwSwapBuffers(m_Window);

    /* Poll for and process events */
    glfwPollEvents();
}

void SigmaEngine::Window::close() {
    glfwTerminate();
}
