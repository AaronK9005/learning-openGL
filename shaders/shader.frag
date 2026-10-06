#version 330 core
out vec4 FragColor;

uniform vec4 ourColor; // set in openGL code

void main()
{
    FragColor = ourColor; // vec4(1.0f, 0.05f, 0.2f, 1.0f);
}