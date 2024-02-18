#version 330 core

out vec4 FragColor;
in vec3 FragNormal;
in vec4 FragPos;

uniform vec3 color;
uniform float alpha;
uniform float enableColors;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

uniform sampler2D shadowMap;
uniform mat4 lightSpaceMatrix;

float getShadow() {
    vec4 lightView_Position = lightSpaceMatrix * FragPos * 0.5 + 0.5;
    lightView_Position.z = min(lightView_Position.z, 1.0);

    float dotLightNormal = max(dot(FragNormal, normalize(lightPosition - FragPos.xyz)), 0.1);
    float bias = 0.01; // max(0.0005 * (1 - dotLightNormal), 0.0001);

    float shadow = texture(shadowMap, lightView_Position.xy).r;

    return (shadow + bias) < lightView_Position.z ? 0.0 : 1.0;
}

vec3 getLighting() {
    float ambientStrength = 0.7;
    float diffuseStrength = 0.3;
    float specularStrength = 0.6;

    // ambient
    vec3 ambient = ambientStrength * color.rgb;

    // diffuse
    vec3 lightDir = normalize(lightPosition - FragPos.xyz);
    float diff = max(dot(FragNormal, lightDir), 0.0);
    vec3 diffuse = diffuseStrength * diff * vec3(0.8, 0.8, 0.8);

    // Specular
    vec3 viewDir = normalize(viewPosition - FragPos.xyz);
    vec3 reflectDir = reflect(-lightDir, FragNormal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); // shininess factor
    vec3 specular = specularStrength * spec * color.rgb;

    // shadow
    float shadow = getShadow();

    return (ambient + (diffuse + specular) * shadow) * color.rgb;
}

void main() {
    vec3 lighting = getLighting();

    FragColor = vec4(lighting, alpha);
}