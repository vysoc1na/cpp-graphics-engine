#ifndef CORE_SHADER_H
#define CORE_SHADER_H

#include <iostream>
#include <GLFW/glfw3.h>

class Shader {
public:
    Shader(const char *vertexShaderSource, const char *fragmentShaderSource);
    ~Shader();

    GLuint getShaderProgram() {
        return shaderProgram;
    }

private:
    GLuint shaderProgram {};

    GLuint loadShaderFromSource(const char* shaderSource, GLenum shaderType);
    void checkShaderCompileErrors(GLuint shader, const std::string &type);
};

#endif // CORE_SHADER_H