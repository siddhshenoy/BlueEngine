#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace BlueEngine
{
    class Window
    {
    private:
        GLFWwindow* m_Window;
        void (*fn_RenderFunction)();
    public:
        Window();
        Window(int locx, int locy, int width, int height, const char* title);
        void Create(int locx, int locy, int width, int height, const char* title);
        //void SetIcon(const char* imagePath);
        void SetRenderFunction(void (*p)())
        {
            this->fn_RenderFunction = p;
        }
        void Loop();
        void CleanUp();
        ~Window();
    public:
        static void GLFWWindowErrorCallback(int error, const char* desc);
    };
}
#endif // WINDOW_H
