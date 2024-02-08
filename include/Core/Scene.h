#ifndef CORE_SCENE_H
#define CORE_SCENE_H

#include <Core/Mesh.h>

class Scene {
public:
    Scene();
    ~Scene();

    void update(glm::mat4 view, glm::mat4 projection, float deltaTime);

    std::vector<Mesh*> children;
};

#endif // CORE_SCENE_H