#include <Core/Shader.h>

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    const char* vertexShaderSource = loadShaderFromFile(vertexShaderPath);
    const char* fragmentShaderSource = loadShaderFromFile(fragmentShaderPath);

    GLuint vertexShader = loadShaderFromSource(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = loadShaderFromSource(fragmentShaderSource, GL_FRAGMENT_SHADER);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
}

Shader::~Shader() {
    glDeleteProgram(shaderProgram);
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

const char* Shader::loadShaderFromFile(const char* filePath) {
    std::ifstream shaderFile(filePath);
    std::stringstream shaderStream;

    if (!shaderFile.is_open()) {
        std::cerr << "Error: Unable to open shader file - " << filePath << std::endl;
        std::exit(-1);
    }

    shaderStream << shaderFile.rdbuf();
    shaderFile.close();

    return strdup(shaderStream.str().c_str());
}

GLuint Shader::loadShaderFromSource(const char* shaderSource, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    checkShaderCompileErrors(shader, "Shader");

    return shader;
}