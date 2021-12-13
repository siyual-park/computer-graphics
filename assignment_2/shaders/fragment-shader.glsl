#version 330 core

in vec3 EntryPoint;

out vec4 FragColor;

void main()
{
    FragColor = vec4(EntryPoint, 1.0);
}