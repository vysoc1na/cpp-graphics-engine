#include <iostream>
#include <Core/Scene.h>

Scene::Scene() = default;

Scene::~Scene() = default;

void Scene::add(Mesh& mesh) {
    children.push_back(mesh);
}

void Scene::update(glm::mat4 view, glm::mat4 projection, float deltaTime) {
    float velocity = deltaTime * 0.01f;

    for (Mesh& mesh : children) {
        mesh.geometry->setRotation(mesh.geometry->getRotation() + glm::vec3(velocity));

        mesh.render(view, projection, deltaTime);
    }
}