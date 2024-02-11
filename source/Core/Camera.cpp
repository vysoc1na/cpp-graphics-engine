#include <cmath>

#include <Core/Camera.h>

Camera::Camera(glm::vec3 inputPosition, glm::ivec2 inputResolution) {
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    right = glm::vec3(1.0f, 0.0f, 0.0f);

    yaw = 270.0f;
    pitch = 0.0f;
    speed = 0.002f;
    sensitivity = 0.01f;

    position = inputPosition;
    resolution = inputResolution;

    projection = glm::perspective(
        glm::radians(45.0f), static_cast<float>(resolution.x) / static_cast<float>(resolution.y), 0.1f, 64.0f
    );
    view = glm::lookAt(
        position, position + front, up
    );
    model = glm::mat4(1.0f);
}

Camera::~Camera() = default;

void Camera::update(GLFWwindow *window, float deltaTime) {
    float keyboardVelocity = speed * deltaTime;
    float mouesVelocity = sensitivity * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position += front * keyboardVelocity;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position -= front * keyboardVelocity;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position -= glm::normalize(glm::cross(front, up)) * keyboardVelocity;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position += glm::normalize(glm::cross(front, up)) * keyboardVelocity;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        position += up * keyboardVelocity;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        position -= up * keyboardVelocity;
    }

    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        mouseDelta = glm::vec2(mouseX - mousePosition.x, mouseY - mousePosition.y);

        yaw += mouseDelta.x * mouesVelocity;
        pitch -= mouseDelta.y * mouesVelocity;
        pitch = fmax(-89.0f, fmin(89.0f, pitch));

        updateVectors();
    }

    updateView();

    mousePosition = glm::vec2(mouseX, mouseY);
}

void Camera::updateVectors() {
    float yawRadians = glm::radians(yaw);
    float pitchRadians = glm::radians(pitch);

    front = glm::normalize(
        glm::vec3(
            glm::cos(yawRadians) * glm::cos(pitchRadians),
            glm::sin(pitchRadians),
            glm::sin(yawRadians) * glm::cos(pitchRadians)
        )
    );
    right = glm::normalize(
        glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f))
    );
    up = glm::normalize(
        glm::cross(right, front)
    );
}

void Camera::updateView() {
    view = glm::lookAt(
        position, position + front, up
    );
}