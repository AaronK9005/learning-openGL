#pragma once

#include <glad/gl.h>

#include <string>

namespace learning
{
    struct Shader
    {
        unsigned id;

        Shader(const char* vertPath, const char* fragPath);

        void use();

        // for setting uniform variables in the shader
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
    };
}