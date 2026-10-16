#include "shader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char* vertPath, const char* fragPath)
{
    std::string vertCode;
    std::string fragCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // ensure ifstream objects can throw exceptions
    vShaderFile.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    fShaderFile.exceptions ( std::ifstream::failbit | std::ifstream::badbit );

    try
    {
        vShaderFile.open(vertPath);
        fShaderFile.open(fragPath);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertCode = vShaderStream.str();
        fragCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n" << e.what() << std::endl;
    }

    const char* vShaderCode = vertCode.c_str();
    const char* fShaderCode = fragCode.c_str();

    unsigned vertex, fragment;
    int success;
    char infoLog[512];
    
    // vert compile
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION::FAILED\n" << infoLog << std::endl;
    }

    // frag compile
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION::FAILED\n" << infoLog << std::endl;
    }

    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(id);
}

void Shader::setBool(std::string_view name, bool value) const
{
    glUniform1i(glGetUniformLocation(id, name.data()), (int)value);
}

void Shader::setInt(std::string_view name, int value) const
{
    glUniform1i(glGetUniformLocation(id, name.data()), value);
}

void Shader::setFloat(std::string_view name, float value) const
{
    glUniform1f(glGetUniformLocation(id, name.data()), value);
}

void Shader::setVec2(std::string_view name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(id, name.data()), x, y);
}

void Shader::setVec2(std::string_view name, const glm::vec2& vec) const
{
    glUniform2f(glGetUniformLocation(id, name.data()), vec.x, vec.y);
}

void Shader::setVec3(std::string_view name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(id, name.data()), x, y, z);
}

void Shader::setVec3(std::string_view name, const glm::vec3& vec) const
{
    glUniform3f(glGetUniformLocation(id, name.data()), vec.x, vec.y, vec.z);
}

void Shader::setMat4(std::string_view name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(id, name.data()), 1, GL_FALSE, glm::value_ptr(mat));
}

