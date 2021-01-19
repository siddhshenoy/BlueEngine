#include <iostream>

#define     GLEW_STATIC

#include "Core/Window.h"
#include "Renderer/Shader.h"

using namespace std;
using namespace BlueEngine;

Shader basicShader;

void RenderLoop();

int main()
{
    Window* EngineWindow = new Window();


    EngineWindow->Create(0, 0, 800, 600, "BlueEngine v0.1a");
    EngineWindow->SetRenderFunction(&RenderLoop);
    basicShader.Load("./res/shaders/basicShader");
    EngineWindow->Loop();
    return 0;
}

void RenderLoop()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    basicShader.UseShader();
    glBegin(GL_TRIANGLES);

    glVertex3f( -0.5f, -0.5f, 0.0f);
    glVertex3f(  0.0f, 0.5f, 0.0f);
    glVertex3f( 0.5f, -0.5f, 0.0f);
    glEnd();
}
