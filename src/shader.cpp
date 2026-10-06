#include "shader.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>

#include <glad/gl.h>
// #include <GL/GL.h>

Shader::Shader() {}

Shader::~Shader() {
    if (id)
    {
        this->destroy();
    }
}

bool Shader::compile(const char* filename)
{
    if (!filename) return false;

    std::filesystem::path path(filename);
    std::ifstream file(path, std::ios::binary | std::ios::ate);

    if (!file.is_open()) return false;

    size_t filesize = static_cast<size_t>(file.tellg());
    std::vector<char> src_buffer(filesize + 1);
    file.seekg(0);
    if (!file.read(src_buffer.data(), filesize))
    {
        return false;
    }
    file.close();
    src_buffer.emplace_back('\0');

    GLenum shaderType;
    
    if (path.extension() == ".vert")
        shaderType = GL_VERTEX_SHADER;
    else if (path.extension() == ".frag")
        shaderType = GL_FRAGMENT_SHADER;
    else 
        return false;

    if (id)
    {
        this->destroy();
    }
    id = glCreateShader(shaderType);

    if (!id)
    {
        return false;
    }

    const char* src = src_buffer.data();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        reportError(filename);
        this->destroy();
        return false;
    }

    return true;
}

void Shader::reportError(const char* filename)
{
    const int size = 512;
    char infoLog[size];

    glGetShaderInfoLog(id, size, nullptr, infoLog);

    std::cerr << "ERROR::SHADER::COMPILATION::FAILED - '" << filename << "'\n" << infoLog << std::endl;
}

void Shader::destroy()
{
    glDeleteShader(id);
    id = 0;
}