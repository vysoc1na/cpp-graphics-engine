#ifndef CORE_SHADER_H
#define CORE_SHADER_H

#include <iostream>
#include <GLFW/glfw3.h>

class Shader {
public:
    Shader();
    ~Shader();

    const char* vertexShaderSource = R"(
        #version 330 core

        layout (location = 0) in vec3 position;
        layout (location = 1) in vec3 normal;

        out vec4 FragPos;
        out vec3 FragNormal;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main() {
            FragPos = model * vec4(position, 1.0);
            FragNormal = mat3(transpose(inverse(model))) * normal;

            gl_Position = projection * view * model * vec4(position, 1.0);
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 330 core

        out vec4 FragColor;
        in vec3 FragNormal;
        in vec4 FragPos;

        uniform vec3 color;
        uniform float alpha;
        uniform vec3 lightDirection = vec3(-1.0, -0.5, -1.0);

        uniform sampler2DShadow shadowMap;
        uniform mat4 lightSpaceMatrix;

        mat4 shadowBias = mat4(
            0.5, 0.0, 0.0, 0.0,
            0.0, 0.5, 0.0, 0.0,
            0.0, 0.0, 0.5, 0.0,
            0.5, 0.5, 0.5, 1.0
        );

        float getShadow() {
            vec4 lightView_Position = shadowBias * lightSpaceMatrix * FragPos;
            vec3 p = lightView_Position.xyz / lightView_Position.w;

            // float shadow = texture(shadowMap, p.xy).r < p.z ? 0.5 : 1.0;
            float shadow = textureProj(shadowMap, lightView_Position);

            return shadow;
        }

        vec3 getLighting() {
            float ambientStrength = 0;
            float diffuseStrength = max(dot(FragNormal, -lightDirection), 0.0);
            vec3 ambient = ambientStrength * color.rgb;
            vec3 diffuse = diffuseStrength * color.rgb;

            return ambient + diffuse;
        }

        void main() {
            vec3 lighting = getLighting();
            float shadow = getShadow();

            FragColor = vec4(lighting * shadow, alpha);
        }

/*
        void main() {
            FragColor = vec4(color, alpha);
            vec3 normal = normalize(FragNormal);
            float ambientStrength = 0.2;
            float diffuseStrength = max(dot(normal, -lightDirection), 0.0);
            vec3 ambient = ambientStrength * color.rgb;
            vec3 diffuse = diffuseStrength * color.rgb;

            // Calculate light direction in view space
            vec3 lightDirView = vec3(lightSpaceMatrix * vec4(-lightDirection, 0.0));

            // Project fragment coordinates into light space
            vec4 fragCoordsLight = lightSpaceMatrix * vec4(gl_FragCoord.xyz, 1.0);

            // Normalize homogeneous coordinates
            vec3 fragCoordsNormalized = fragCoordsLight.xyz / fragCoordsLight.w;

            // Calculate shadow factor
            float shadowFactor = texture(shadowMap, gl_FragCoord.xyz);

            vec3 lighting = ambient + diffuse;

            if (shadowFactor > 0.0) {
                FragColor = vec4(0.0, 1.0, 0.0, alpha);
            } else {
                FragColor = vec4(lighting, alpha);
            }
        }
*/
    )";

    const char* fragmentShaderShadowsSource = R"(
        #version 330 core

        out vec4 FragColor;

        uniform vec3 color;
        uniform float alpha;

        void main() {
            FragColor = vec4(vec3(0), alpha);
        }
    )";

    GLuint getShaderProgram() {
        return shaderProgram;
    }

    GLuint getShaderProgramShadows() {
        return shaderProgramShadows;
    }

private:
    GLuint vertexShader {};
    GLuint fragmentShader {};

    GLuint fragmentShaderShadows {};

    GLuint shaderProgram {};
    GLuint shaderProgramShadows {};

    GLuint loadShaderFromSource(const char* shaderSource, GLenum shaderType);
    void checkShaderCompileErrors(GLuint shader, const std::string &type);
};

#endif // CORE_SHADER_H