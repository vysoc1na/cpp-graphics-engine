#ifndef CORE_SHADER_H
#define CORE_SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
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

    static GLuint loadShaderFromSource(const char* shaderSource, GLenum shaderType);
    static const char* loadShaderFromFile(const char* filePath);
    static void checkShaderCompileErrors(GLuint shader, const std::string &type);
};

#endif // CORE_SHADER_H