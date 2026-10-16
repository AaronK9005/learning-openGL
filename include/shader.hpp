#pragma once

#include <glad/gl.h>

#include <string_view>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

struct Shader
{
    unsigned id;

    Shader(const char* vertPath, const char* fragPath);

    void use();

    // for setting uniform variables in the shader
    void setBool(std::string_view, bool value) const;
    void setInt(std::string_view name, int value) const;
    void setFloat(std::string_view name, float value) const;

    void setVec2(std::string_view name, float x, float y) const;
    void setVec2(std::string_view name, const glm::vec2& vec) const;

    void setVec3(std::string_view name, float x, float y, float z) const;
    void setVec3(std::string_view name, const glm::vec3& vec) const;

    void setMat4(std::string_view name, const glm::mat4& mat) const;
};