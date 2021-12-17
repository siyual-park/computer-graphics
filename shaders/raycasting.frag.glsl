#version 330 core

in vec3 EntryPoint;
in vec4 ExitPointCoord;

out vec4 FragColor;

uniform sampler2D ExitPoints;
uniform sampler3D VolumeTex;
//uniform sampler1D TransferFunc;
//uniform float     StepSize;
uniform vec2      ScreenSize;

void main() {
    float StepSize = 0.001f;

    vec3 exitPoint = texture(ExitPoints, gl_FragCoord.st / ScreenSize).xyz;
    if (EntryPoint == exitPoint) {
        discard;
    }

    vec3 dir = exitPoint - EntryPoint;
    float len = length(dir);

    vec3 deltaDir = normalize(dir) * StepSize;
    float deltaDirLen = length(deltaDir);

    vec3 voxelCoord = EntryPoint;
    vec4 colorAcum = vec4(0.0);
    float alphaAcum = 0.0;
    float intensity;
    float lengthAcum = 0.0;
    vec4 colorSample;
    float alphaSample;
    vec4 bgColor = vec4(1.0, 1.0, 1.0, 0.0);

    while (true) {
        float norm = 0.0f;

        intensity = texture(VolumeTex, voxelCoord).x;
        if (intensity > 325) {
            norm = 1.0f;
        } else if (intensity < 119) {
            norm = 0.0f;
        } else {
            norm = (intensity - 119) / (325 - 119);
        }

        colorSample = vec4(norm);
        if (colorSample.a > 0.0) {
            colorAcum.rgb += colorSample.rgb * colorSample.a;
            colorAcum.a += colorSample.a;
        }

        voxelCoord += deltaDir;
        lengthAcum += deltaDirLen;

        if (lengthAcum >= len) {
            break;
        } else if (colorAcum.a > 1.0) {
            colorAcum.a = 1.0;
            break;
        }
    }

    FragColor = colorAcum;
}