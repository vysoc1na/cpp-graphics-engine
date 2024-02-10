#include <Core/Shader.h>

Shader::Shader() {
    vertexShader = loadShaderFromSource(vertexShaderSource, GL_VERTEX_SHADER);
    fragmentShader = loadShaderFromSource(fragmentShaderSource, GL_FRAGMENT_SHADER);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    fragmentShaderShadows = loadShaderFromSource(fragmentShaderShadowsSource, GL_FRAGMENT_SHADER);

    shaderProgramShadows = glCreateProgram();
    glAttachShader(shaderProgramShadows, vertexShader);
    glAttachShader(shaderProgramShadows, fragmentShaderShadows);
    glLinkProgram(shaderProgramShadows);
}

Shader::~Shader() {
    glDeleteProgram(shaderProgram);
    glDeleteProgram(shaderProgramShadows);
}

void Shader::checkShaderCompileErrors(GLuint shader, const std::string &type) {
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Error: " << type << " compilation failed\n" << infoLog << std::endl;
        std::exit(-1);
    }
}

GLuint Shader::loadShaderFromSource(const char* shaderSource, GLenum shaderType) {
    // Create and compile shader
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    // Check for shader compilation errors
    checkShaderCompileErrors(shader, "Shader");

    return shader;
}
