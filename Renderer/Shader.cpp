#include "Shader.h"

namespace BlueEngine {
Shader::Shader()
{
    //ctor
}

void Shader::Load(const std::string& filePath)
{
    //First Load the vertex shader..
    std::string Source;
    const char* m_ShaderSources[TOTAL_SHADERS];
    int m_ShaderSourceLength[TOTAL_SHADERS];
    this->m_Shaders[VERTEX_SHADER] = glCreateShader(GL_VERTEX_SHADER);
    Source = LoadShader(filePath + ".vs");
    m_ShaderSources[VERTEX_SHADER] = Source.c_str();
    m_ShaderSourceLength[VERTEX_SHADER] = Source.length();
    glShaderSource(this->m_Shaders[VERTEX_SHADER], 1, &m_ShaderSources[VERTEX_SHADER], &m_ShaderSourceLength[VERTEX_SHADER]);
    if(!CompileShader(this->m_Shaders[VERTEX_SHADER]))
    {
        std::cout << "Compilation of shader '" << filePath << "' failed.." << std::endl;
        std::cout << GetShaderError(this->m_Shaders[VERTEX_SHADER]);
    }

    //First Load the fragment shader..

    this->m_Shaders[FRAGMENT_SHADER] = glCreateShader(GL_FRAGMENT_SHADER);
    Source = LoadShader(filePath + ".fs");
    m_ShaderSources[FRAGMENT_SHADER] = Source.c_str();
    m_ShaderSourceLength[FRAGMENT_SHADER] = Source.length();
    glShaderSource(this->m_Shaders[FRAGMENT_SHADER], 1, &m_ShaderSources[FRAGMENT_SHADER], &m_ShaderSourceLength[FRAGMENT_SHADER]);
    if(!CompileShader(this->m_Shaders[FRAGMENT_SHADER]))
    {
        std::cout << "Compilation of shader '" << filePath << "' failed.." << std::endl;
        std::cout << GetShaderError(this->m_Shaders[FRAGMENT_SHADER]);
    }

    //Create the program..

    this->m_Program = CreateProgram(this->m_Shaders, TOTAL_SHADERS);
    glLinkProgram(this->m_Program);
}

std::string Shader::LoadShader(const std::string& source)
{
    std::string FileData = "",
                LineData = "";
    std::fstream ShaderFile;
    ShaderFile.open(source, std::fstream::in);

    if(ShaderFile.good())
    {
        while(!ShaderFile.eof())
        {
            std::getline(ShaderFile, LineData);
            FileData += LineData + "\r\n";
        }
    }
    else
    {
        std::cout << "SHADER ERROR: File '" << source << "' does not exist!" << std::endl;
    }
    ShaderFile.close();
    return FileData;
}
bool Shader::CompileShader(GLuint shaderID)
{
    GLint compileStatus;
    glCompileShader(shaderID);
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileStatus);
    return compileStatus;
}
std::string Shader::GetShaderError(GLuint shaderID)
{
    std::string errorString = "";
    std::cout << "Vertex Shader Compilation failed!" << std::endl;
    int logLength;
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
    char* log = new char[logLength];
    glGetShaderInfoLog(shaderID, logLength, NULL, log);
    errorString = std::string(log);
    delete log;
    return errorString;
}
GLuint Shader::CreateProgram(GLuint* shaders,int totalShaders)
{
    GLuint program = glCreateProgram();
    for(int i = 0; i < totalShaders; i++)
    {
        glAttachShader(program, shaders[i]);
    }
    return program;
}
void Shader::UseShader()
{
    std::cout << "Using the program" << std::endl;
    glUseProgram(this->m_Program);
}

Shader::~Shader()
{
    //dtor
}

}
