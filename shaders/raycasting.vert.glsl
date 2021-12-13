#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 EntryPoint;
out vec4 ExitPointCoord;

uniform mat4 model;
uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * world * model * vec4(aPos, 1.0);

    ExitPointCoord = gl_Position;
    EntryPoint = aColor;
}