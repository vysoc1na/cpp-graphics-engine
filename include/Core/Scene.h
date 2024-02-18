#ifndef CORE_SCENE_H
#define CORE_SCENE_H

#include <Core/Mesh.h>
#include <Core/ShadowMap.h>

class Scene {
public:
    Scene();
    ~Scene();

    void update(glm::mat4 view, glm::mat4 projection, glm::vec3 viewPosition, ShadowMap* shadowMap, float deltaTime);

    void renderShadows(glm::vec3 lightPosition, glm::vec3 viewPosition, ShadowMap* shadowMap, float deltaTime);
    void renderScene(glm::mat4 view, glm::mat4 projection, glm::vec3 viewPosition, ShadowMap* shadowMap, float deltaTime);

    std::vector<Mesh*> children;
};

#endif // CORE_SCENE_H