#ifndef CORE_CAMERA_H
#define CORE_CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(glm::vec3 position, glm::ivec2 resolution);
    ~Camera();

    void update(GLFWwindow *window, float deltaTime);

    glm::mat4 getProjection() {
        return projection;
    }
    glm::mat4 getView() {
        return view;
    }
    glm::mat4 getModel() {
        return model;
    }

    glm::vec3 getPosition() {
        return position;
    }

private:
    glm::vec3 front {};
    glm::vec3 up {};
    glm::vec3 right {};

    float yaw;
    float pitch;
    float speed;
    float sensitivity;
    glm::vec2 mousePosition {};
    glm::vec2 mouseDelta {};

    glm::mat4 projection {};
    glm::mat4 view {};
    glm::mat4 model {};

    glm::vec3 position {};
    glm::ivec2 resolution {};

    void updateVectors();
    void updateView();
};

#endif // CORE_CAMERA_H