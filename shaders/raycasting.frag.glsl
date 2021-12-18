#version 330 core

in vec3 FragPos;
in vec3 EntryPoint;
in vec4 ExitPointCoord;

out vec4 FragColor;

uniform sampler1D TransferFunc;
uniform sampler2D ExitPoints;
uniform sampler3D VolumeTex;
uniform vec2      ScreenSize;
uniform vec3      VolumeSize;
uniform vec3      VolumeSpacing;

float calculate_step(vec3 normDir) {
    float x = pow(abs(normDir.x * VolumeSize.x), 2);
    float y = pow(abs(normDir.y * VolumeSize.y), 2);
    float z = pow(abs(normDir.z * VolumeSize.z), 2);

    return pow(x + y + z, 0.5);
}

float calculate_weight(vec3 normDir) {
    vec3 normSpacing = normalize(VolumeSpacing);

    float x = pow(abs(normDir.x * normSpacing.x), 2);
    float y = pow(abs(normDir.y * normSpacing.y), 2);
    float z = pow(abs(normDir.z * normSpacing.z), 2);

    return pow(x + y + z, 0.5);
}

void main() {
    vec2 exitFragCoord = (ExitPointCoord.xy / ExitPointCoord.w + 1.0f) / 2.0f;
    vec3 exitPoint = texture(ExitPoints, exitFragCoord).xyz;

    if (exitPoint == EntryPoint) {
        FragColor = vec4(0.0f);
        return;
    }

    vec3 dir = exitPoint - EntryPoint;
    float len = length(dir);

    vec3 normDir = normalize(dir);

    float step = calculate_step(normDir);
    float stepSize = 1.0f / step;

    float weight = calculate_weight(normDir);

    vec3 deltaDir = normDir * stepSize;
    float deltaDirLen = length(deltaDir);

    vec3 voxelCoord = EntryPoint;

    vec4 colorAcum = vec4(0.0f);
    float lengthAcum;

    vec4 backgoundColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

    for (int i = 0; i < step * 2; i++) {
        float intensity = (texture(VolumeTex, voxelCoord).x + 1.0f) / 2.0f;
        vec4 colorSample = texture(TransferFunc, intensity);

        if (colorSample.a > 0.0f) {
            colorSample.a = 1.0 - pow(1.0 - colorSample.a, weight);
            colorAcum.rgb += (1.0f - colorAcum.a) * colorSample.rgb * colorSample.a;
            colorAcum.a += (1.0f - colorAcum.a) * colorSample.a;
        }

        voxelCoord += deltaDir;
        lengthAcum += deltaDirLen;

        if (lengthAcum >= len) {
            colorAcum.rgb = colorAcum.rgb * colorAcum.a;
            break;
        } else if (colorAcum.a > 1.0f) {
            colorAcum.a = 1.0f;
            break;
        }
    }

    FragColor = colorAcum;
}