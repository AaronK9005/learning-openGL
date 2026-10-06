#pragma once


class Shader
{
    unsigned id = 0;

    void reportError(const char* filename);

public:
    Shader();
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    bool compile(const char* filename);
    void destroy();

    unsigned get() { return id; }
};