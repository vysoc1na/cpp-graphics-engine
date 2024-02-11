#include "include/Core/Renderer.h"

#include <iterator>

Renderer::Renderer(glm::ivec2 inputResolution) {
    resolution = inputResolution;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        std::exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(resolution.x, resolution.y, "renderer", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        std::exit(-1);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwWindowHint(GLFW_REFRESH_RATE, 120);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        std::exit(-1);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glfwSetFramebufferSizeCallback(window, reinterpret_cast<GLFWframebuffersizefun>(framebufferSizeCallback));
}

Renderer::~Renderer() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Renderer::run(Camera camera, Scene scene, ShadowMap* shadowMap) {
    while (!glfwWindowShouldClose(window)) {
        // render rest as normal
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        camera.update(window, 8.3);

        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.update(camera.getView(), camera.getProjection(), shadowMap, 16.0f);

        glfwSwapBuffers(window);
        glfwPollEvents();

        showFPS();
    }
}

void Renderer::showFPS() {
    double currentTime = glfwGetTime();
    double delta = currentTime - lastTime;
    nbFrames++;

    if (delta >= 0.1) {
        double fps = double(nbFrames) / delta;

        std::ostringstream newTitle;
        newTitle << "fps: " << trunc(fps);

        glfwSetWindowTitle(window, newTitle.str().c_str());

        nbFrames = 0;
        lastTime = currentTime;
    }
}

void Renderer::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}