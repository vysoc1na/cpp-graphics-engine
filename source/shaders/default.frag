#version 330 core

out vec4 FragColor;
in vec3 FragNormal;
in vec4 FragPos;

uniform vec3 color;
uniform float alpha;
uniform float enableColors;
uniform vec3 lightPosition;

uniform sampler2D shadowMap;
uniform mat4 lightSpaceMatrix;

float getShadow() {
    vec4 lightView_Position = lightSpaceMatrix * FragPos * 0.5 + 0.5;

    float dotLightNormal = max(dot(FragNormal, normalize(lightPosition - FragPos.xyz)), 0.1);
    float bias = max(0.0005 * (1 - dotLightNormal), 0.0001);

    float shadow = texture(shadowMap, lightView_Position.xy).r;

    if (lightView_Position.z > 1.0) {
        lightView_Position.z = 1.0;
    }

    return (shadow + bias) < lightView_Position.z ? 0.3 : 1.0;
}

vec3 getLighting() {
    float ambientStrength = 0.8;
    float diffuseStrength = max(dot(FragNormal, normalize(lightPosition - FragPos.xyz)), 0.0);
    vec3 ambient = ambientStrength * color.rgb;
    vec3 diffuse = diffuseStrength * color.rgb;

    return ambient + diffuse;
}

void main() {
    vec3 lighting = getLighting();
    float shadow = getShadow();

    FragColor = vec4(lighting * shadow, alpha);
}