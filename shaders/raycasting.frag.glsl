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
    int acc = 0;

    while (true) {
        float nor = 0.0f;

        intensity = texture(VolumeTex, voxelCoord).x;
        if (intensity > 325) {
            nor = 1.0f;
        } else if (intensity < 119) {
            nor = 0.0f;
        } else {
            nor = (intensity - 119) / (325 - 119);
        }
        if (intensity > 0) {
            acc++;
        }

        colorSample = vec4(nor, nor, nor, nor);
        if (colorSample.a > 0.0) {
            colorSample.a = 1.0 - pow(1.0 - colorSample.a, StepSize * 200.0f);
            colorAcum.rgb += (1.0 - colorAcum.a) * colorSample.rgb * colorSample.a;
            colorAcum.a += (1.0 - colorAcum.a) * colorSample.a;
        }

        voxelCoord += deltaDir;
        lengthAcum += deltaDirLen;

        if (lengthAcum >= len) {
            //            colorAcum.rgb = colorAcum.rgb * colorAcum.a + (1 - colorAcum.a) * bgColor.rgb;
            break;
        } else if (colorAcum.a > 1.0) {
            colorAcum.a = 1.0;
            break;
        }
    }

    FragColor = colorAcum;
}