#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

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

uniform vec3 viewPos;
uniform mat4 model;
uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

uniform Material material;
uniform Light    light;

float calculateStep(vec3 normDir) {
    return dot(abs(normDir), abs(VolumeSize));
}

float calculateWeight(vec3 normDir) {
    return dot(abs(normDir), abs(normalize(VolumeSpacing)));
}

float intensity(vec3 voxelCoord) {
    return texture(VolumeTex, voxelCoord).x;
}

bool isInTextureCoord(float value) {
    return value >= 0.0f && value <= 1.0f;
}

bool isInTextureCoord(vec3 value) {
    return isInTextureCoord(value.x) && isInTextureCoord(value.y) && isInTextureCoord(value.z);
}

float zeroToOne(float value) {
    return max(min(value, 1.0f), 0.0f);
}

vec3 normalizeColor(vec3 color) {
    return vec3(zeroToOne(color.x), zeroToOne(color.y), zeroToOne(color.z));
}

vec4 normalizeColor(vec4 color) {
    return vec4(normalizeColor(color.xyz), zeroToOne(color.a));
}

vec4 sampling(vec3 voxelCoord) {
    if (!isInTextureCoord(voxelCoord)) {
        return vec4(0.0f);
    }

    return normalizeColor(texture(TransferFunc, (intensity(voxelCoord) + 1.0f) / 2.0f));
}

float samplingForNormal(vec3 voxelCoord) {
    if (!isInTextureCoord(voxelCoord)) {
        return 0.0f;
    }
    return intensity(voxelCoord);
}

vec3 calculateNormal(vec3 voxelCoord, vec3 unitVoxelSize) {
    float xFront = samplingForNormal(vec3(voxelCoord.x + unitVoxelSize.x, voxelCoord.y, voxelCoord.z));
    float xBack = samplingForNormal(vec3(voxelCoord.x - unitVoxelSize.x, voxelCoord.y, voxelCoord.z));
    float yFront = samplingForNormal(vec3(voxelCoord.x, voxelCoord.y + unitVoxelSize.y, voxelCoord.z));
    float yBack = samplingForNormal(vec3(voxelCoord.x, voxelCoord.y - unitVoxelSize.y, voxelCoord.z));
    float zFront = samplingForNormal(vec3(voxelCoord.x, voxelCoord.y, voxelCoord.z + unitVoxelSize.z));
    float zBack = samplingForNormal(vec3(voxelCoord.x, voxelCoord.y, voxelCoord.z - unitVoxelSize.z));

    return vec3(xFront - xBack, yFront - yBack, zFront - zBack) / (unitVoxelSize * 2.0f);
}

vec3 changeToWorldCoord(vec3 voxelCoord) {
    return vec3(world * model * vec4(voxelCoord, 1.0));
}

vec4 applyShadow(vec4 colorSample, vec3 voxelCoord, vec3 unitVoxelSize) {
    vec3 ambient = light.ambient * colorSample.rgb;

    vec3 fragCoord = changeToWorldCoord(voxelCoord);
    vec3 normCoord = normalize(calculateNormal(voxelCoord, unitVoxelSize)) + voxelCoord;
    vec3 norm = normalize(changeToWorldCoord(normCoord) - fragCoord);

    vec3 lightDir = normalize(light.position - fragCoord);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = light.diffuse * diff * colorSample.rgb;

    vec3 viewDir = normalize(viewPos - fragCoord);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * colorSample.rgb;

    float distance = length(light.position - fragCoord);
    float attenuation = 1 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = normalizeColor(ambient) + normalizeColor(diffuse) + normalizeColor(specular);

    return normalizeColor(vec4(result.xyz, colorSample.a));
}

void main() {
    vec2 exitFragCoord = (ExitPointCoord.xy / ExitPointCoord.w + 1.0f) / 2.0f;
    vec3 exitPoint = texture(ExitPoints, exitFragCoord).xyz;

    if (exitPoint == EntryPoint) {
        discard;
    }

    vec3 dir = exitPoint - EntryPoint;
    float len = length(dir);

    vec3 normDir = normalize(dir);

    float step = calculateStep(normDir);
    float stepSize = abs(dot(vec3(1.0f, 1.0f, 1.0f), abs(normDir))) / step;

    float weight = calculateWeight(normDir);

    vec3 deltaDir = normDir * stepSize;
    float deltaDirLen = length(deltaDir);

    vec3 voxelCoord = EntryPoint;

    vec4 colorAcum = vec4(0.0f);
    float lengthAcum = 0.0f;

    vec3 unitVoxelSize = 1.0f / (VolumeSize * VolumeSpacing) / 2.0f;

    while (true) {
        vec4 colorSample = sampling(voxelCoord);

        if (colorSample.a > 0.0f) {
            colorSample.a = 1.0 - pow(1.0 - colorSample.a, weight);
            colorSample = applyShadow(colorSample, voxelCoord, unitVoxelSize);

            colorAcum.rgb += (1.0f - colorAcum.a) * colorSample.rgb * colorSample.a;
            colorAcum.a += (1.0f - colorAcum.a) * colorSample.a;
        }

        voxelCoord += deltaDir;
        lengthAcum += deltaDirLen;

        if (lengthAcum >= len) {
            if (colorAcum.a > 1.0f) {
                colorAcum.a = 1.0f;
            }
            colorAcum.rgb = colorAcum.rgb * colorAcum.a;
            break;
        } else if (colorAcum.a > 1.0f) {
            colorAcum.a = 1.0f;
            break;
        }
    }

    FragColor = normalizeColor(colorAcum);
}