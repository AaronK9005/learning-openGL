#version 330 core
out vec4 FragColor;

in vec4 vertexColor;

void main()
{
    FragColor = vertexColor; // vec4(1.0f, 0.05f, 0.2f, 1.0f);
}