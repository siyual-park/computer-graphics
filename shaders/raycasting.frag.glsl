#version 330 core

in vec3 EntryPoint;
in vec4 ExitPointCoord;

out vec4 FragColor;

uniform sampler2D ExitPoints;
uniform sampler3D VolumeTex;
uniform vec2      ScreenSize;

void main() {
    float StepSize = 0.001f;

    vec2 exitFragCoord = (ExitPointCoord.xy / ExitPointCoord.w + 1.0f) / 2.0f;
    vec3 exitPoint = texture(ExitPoints, exitFragCoord).xyz;
    if (EntryPoint == exitPoint) {
        FragColor = vec4(0.0f);
        return;
    }

    vec3 dir = exitPoint - EntryPoint;
    float len = length(dir);

    vec3 deltaDir = normalize(dir) * StepSize;
    float deltaDirLen = length(deltaDir);

    vec3 voxelCoord = EntryPoint;
    vec4 colorAcum = vec4(0.0f);
    float lengthAcum;
    vec4 backgoundColor = vec4(1.0f, 1.0f, 1.0f, 0.0f);

    float min = 119.0f / 65535.0f;
    float max = 325.0f / 65535.0f;

    while (true) {
        float alpha = 1.0f;
        float intensity = texture(VolumeTex, voxelCoord).x / 256;

        if (intensity > max) {
            alpha = 1.0f;
        } else if (intensity < min) {
            alpha = 0.0f;
        } else {
            alpha = min * abs(intensity - max) / (max - min) + max * abs(intensity - min) / (max - min);
        }

        vec4 colorSample = vec4(1.0f, 1.0f, 1.0f, alpha);
        if (colorSample.a > 0.0f) {
            colorAcum.rgb += colorSample.rgb * colorSample.a;
            colorAcum.a += colorSample.a;
        }

        voxelCoord += deltaDir;
        lengthAcum += deltaDirLen;

        if (lengthAcum >= len) {
            break;
        } else if (colorAcum.a > 1.0f) {
            colorAcum.a = 1.0f;
            break;
        }
    }

    FragColor = colorAcum;
}