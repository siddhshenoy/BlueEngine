#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <GL/glew.h>


#define     TOTAL_SHADERS       2

namespace BlueEngine {

enum ShaderType
{
    VERTEX_SHADER = 0,
    FRAGMENT_SHADER = 1
};

class Shader
{
private:

    GLuint m_Shaders[TOTAL_SHADERS];
    GLuint m_Program;
public:
    Shader();
    void Load(const std::string& filePath);
    void UseShader();
    ~Shader();
public:
    static std::string LoadShader(const std::string& source);
    static bool CompileShader(GLuint shaderID);
    static std::string GetShaderError(GLuint shaderID);
    //Program
    static GLuint CreateProgram(GLuint* shaders,int totalShaders);

};
}

#endif // SHADER_H
