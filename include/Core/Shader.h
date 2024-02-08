#include <iostream>
#include <GLFW/glfw3.h>

class Shader {
public:
    Shader();
    ~Shader();

    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        void main() {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        uniform vec3 color;
        uniform float alpha;
        void main() {
            // vec2 uv = gl_FragCoord.xy / vec2(1600, 1200);
            FragColor = vec4(color, alpha);
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