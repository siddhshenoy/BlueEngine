#include "Window.h"

namespace BlueEngine
{
    Window::Window()
    {
        this->m_Window = NULL;
    }
    Window::Window(int locx, int locy, int width, int height, const char* title)
    {
        this->Create(locx, locy, width, height, title);
    }
   /* void Window::SetIcon(const char* imagePath)
    {
        if(this->m_Window != NULL)
        {
            GLFWimage image[1];
            image[0].pixels = stbi_load(imagePath, &image[0].width, &image[0].height, 0, 4);
            glfwSetWindowIcon(this->m_Window, 1, image);
            stbi_image_free(image[0].pixels);
        }
    }*/
    void Window::Create(int locx, int locy, int width, int height, const char* title)
    {
        glfwSetErrorCallback(Window::GLFWWindowErrorCallback);

        if(!glfwInit())
        {
            exit(1);
        }


        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        this->m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
        if(!this->m_Window)
        {
            exit(1);
        }
        glfwMakeContextCurrent(this->m_Window);

        GLenum glewError = glewInit();
        if(glewError != GLEW_OK)
        {
            std::cout << "GLEW Initialization failed.." << std::endl;
            std::cout << glewGetErrorString(glewError) << std::endl;
            exit(1);
        }
        glfwSetWindowPos(this->m_Window, locx, locy);
        glfwSwapInterval(1);
    }
    void Window::Loop()
    {
        if(this->m_Window != NULL)
        {
            while(!glfwWindowShouldClose(this->m_Window))
            {
                if(this->fn_RenderFunction != NULL)
                    this->fn_RenderFunction();
                glfwSwapBuffers(this->m_Window);
                glfwPollEvents();
            }
        }
    }
    void Window::CleanUp()
    {
        if(this->m_Window != NULL)
        {
            glfwDestroyWindow(this->m_Window);
            glfwTerminate();
        }
    }
    Window::~Window()
    {
        if(this->m_Window != NULL) {
            this->CleanUp();
        }
    }
    void Window::GLFWWindowErrorCallback(int error, const char* desc)
    {
        std::cout << "[GLFW Window Error]: " << desc << " (Code: " << error << ")" << std::endl;
    }
}
