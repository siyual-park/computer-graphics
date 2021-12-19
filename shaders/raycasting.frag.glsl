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
    float x = pow(abs(normDir.x * VolumeSize.x), 2);
    float y = pow(abs(normDir.y * VolumeSize.y), 2);
    float z = pow(abs(normDir.z * VolumeSize.z), 2);

    return pow(x + y + z, 0.5);
}

float calculateWeight(vec3 normDir) {
    vec3 normSpacing = normalize(VolumeSpacing);

    float x = pow(abs(normDir.x * normSpacing.x), 2);
    float y = pow(abs(normDir.y * normSpacing.y), 2);
    float z = pow(abs(normDir.z * normSpacing.z), 2);

    return pow(x + y + z, 0.5);
}

vec4 sampling(vec3 voxelCoord) {
    float intensity = (texture(VolumeTex, voxelCoord).x + 1.0f) / 2.0f;
    return texture(TransferFunc, intensity);
}

vec3 calculateNormal(vec3 voxelCoord, vec3 unitVoxelSize) {
    float xPlus = sampling(vec3(voxelCoord.x + unitVoxelSize.x, voxelCoord.y, voxelCoord.z)).a;
    float xMinus = sampling(vec3(voxelCoord.x - unitVoxelSize.x, voxelCoord.y, voxelCoord.z)).a;
    float yPlus = sampling(vec3(voxelCoord.x, voxelCoord.y + unitVoxelSize.y, voxelCoord.z)).a;
    float yMinus = sampling(vec3(voxelCoord.x, voxelCoord.y - unitVoxelSize.y, voxelCoord.z)).a;
    float zPlus = sampling(vec3(voxelCoord.x, voxelCoord.y, voxelCoord.z + unitVoxelSize.z)).a;
    float zMinus = sampling(vec3(voxelCoord.x, voxelCoord.y, voxelCoord.z - unitVoxelSize.z)).a;

    float xGradient = xPlus - xMinus;
    float yGradient = yPlus - yMinus;
    float zGradient = zPlus - zMinus;

    return vec3(xGradient, yGradient, zGradient);
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

    vec3 fragDir = vec3(deltaDir.x * VolumeSpacing.x * VolumeSize.x, deltaDir.y * VolumeSpacing.y * VolumeSize.y, deltaDir.z * VolumeSpacing.z * VolumeSize.z);
    fragDir = vec3(world * model * vec4(fragDir, 1.0));

    vec3 voxelCoord = EntryPoint;
    vec3 fragCoord = FragPos;

    vec4 colorAcum = vec4(0.0f);
    float lengthAcum;

    vec4 backgoundColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);

    vec3 unitVoxelSize = 1.0f / VolumeSize;

    for (int i = 0; i < step * 2; i++) {
        vec4 colorSample = sampling(voxelCoord);

        if (colorSample.a > 0.0f) {
            vec3 ambient = light.ambient * colorSample.rgb;

            vec3 norm = normalize(calculate_normal(voxelCoord, unitVoxelSize));
            vec3 lightDir = normalize(light.position - fragCoord);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = light.diffuse * diff * colorSample.rgb;

            vec3 viewDir = normalize(viewPos - fragCoord);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
            vec3 specular = light.specular * spec * colorSample.rgb;

            float distance = length(light.position - fragCoord);
            float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

            ambient *= attenuation;
            diffuse *= attenuation;
            specular *= attenuation;

            vec3 result = ambient + diffuse + specular;

            colorSample = vec4(result.xyz, 1.0 - pow(1.0 - colorSample.a, weight));

            colorAcum.rgb += (1.0f - colorAcum.a) * colorSample.rgb * colorSample.a;
            colorAcum.a += (1.0f - colorAcum.a) * colorSample.a;
        }

        voxelCoord += deltaDir;
        fragCoord += fragDir;
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