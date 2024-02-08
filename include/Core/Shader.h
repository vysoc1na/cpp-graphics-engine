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

        out vec3 FragPos;
        out vec3 FragNormal;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main() {
            FragPos = vec3(model * vec4(position, 1.0));
            FragNormal = mat3(transpose(inverse(model))) * normal;

            gl_Position = projection * view * model * vec4(position, 1.0);
        }
    )";

    const char* fragmentShaderSource = R"(
       #version 330 core
        out vec4 FragColor;
        in vec3 FragNormal;
        uniform vec3 color;
        uniform float alpha;
        uniform vec3 lightDirection = vec3(-0.5, -0.5, -0.5);

        void main() {
            vec3 normal = normalize(FragNormal);
            float ambientStrength = 0.2;
            float diffuseStrength = max(dot(normal, -lightDirection), 0.0);
            vec3 ambient = ambientStrength * color.rgb;
            vec3 diffuse = diffuseStrength * color.rgb;

            vec3 lighting = ambient + diffuse;
            FragColor = vec4(lighting, alpha);
        }
    )";

    GLuint getShaderProgram() {
        return shaderProgram;
    }

private:
    GLuint vertexShader {};
    GLuint fragmentShader {};

    GLuint shaderProgram {};

    GLuint loadShaderFromSource(const char* shaderSource, GLenum shaderType);
    void checkShaderCompileErrors(GLuint shader, const std::string &type);
};