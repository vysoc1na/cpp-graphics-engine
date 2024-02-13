#ifndef CORE_SHADOW_MAP_H
#define CORE_SHADOW_MAP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ShadowMap {
public:
    ShadowMap(int width, int height);
    ~ShadowMap();

    glm::mat4 GetLightSpaceMatrix() {
        return lightSpaceMatrix;
    }
    GLuint GetDepthMap() {
        return depthMap;
    }

    void BindFramebuffer() const;
    static void UnbindFramebuffer();
    void SetupLightSpaceMatrix(glm::mat4 projection, const glm::vec3& lightPosition, const glm::vec3& sceneCenter);

private:
    GLuint depthMapFBO{};
    GLuint depthMap{};

    int width;
    int height;
    glm::mat4 lightSpaceMatrix{};
};

#endif // CORE_SHADOW_MAP_H