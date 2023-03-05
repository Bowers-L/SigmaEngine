#include "Window.h"

#include "SigmaEngine/Core/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

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

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        const char* glsl_version = "#version 330 core";


        /* Create a windowed mode window and its OpenGL context */
        m_Window = glfwCreateWindow(props.width, props.height, props.title.c_str(), NULL, NULL);
        SG_CORE_ASSERT(m_Window != nullptr, "Failed to create GLFW window.");

        /* Make the window's context current */
        glfwMakeContextCurrent(m_Window);

        int gladSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        SG_CORE_ASSERT(gladSuccess, "Failed to initialize GLAD");

        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        //GLCall(glViewport(0, 0, props.width, props.height));
    }

    void Window::initImGuiFrame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    bool Window::shouldClose()
    {
        return glfwWindowShouldClose(m_Window);
    }

    void Window::drawFrame()
    {
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
