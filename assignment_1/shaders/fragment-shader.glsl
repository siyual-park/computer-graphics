#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D model_texture_diffuse1;

void main()
{
    FragColor = texture(model_texture_diffuse1, TexCoords);
}