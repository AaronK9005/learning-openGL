#version 330 core
out vec4 FragColor;

in vec2 TextCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

void main()
{
    FragColor = mix(texture(texture1, TextCoord), texture(texture2, vec2(1.0 - TextCoord.x, TextCoord.y)), mixValue);
}