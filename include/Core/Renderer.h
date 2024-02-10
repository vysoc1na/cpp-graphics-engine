#ifndef CORE_RENDERER_H
#define CORE_RENDERER_H

#include <iostream>
#include <string>
#include <sstream>
#include <array>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Scene.h"
#include "ShadowMap.h"

class Renderer {
public:
    Renderer(glm::ivec2 resolution);
    ~Renderer();

    void run(Camera camera, Scene scene, ShadowMap* shadowMap);

    glm::ivec2 getResolution() {
        return resolution;
    }

private:
    GLFWwindow* window {};
    glm::ivec2 resolution {};

    double lastTime {};
    int nbFrames {};

    void showFPS();
    static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
};

#endif // CORE_RENDERER_H