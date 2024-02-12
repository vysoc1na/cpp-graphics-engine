#include <cmath>
#include <iostream>
#include <Core/Scene.h>

Scene::Scene() = default;

Scene::~Scene() = default;

void Scene::update(glm::mat4 view, glm::mat4 projection, ShadowMap* shadowMap, float deltaTime) {
    double x = cos(glfwGetTime() / 20) * 10.0f;
    double z = sin(glfwGetTime() / 20) * 10.0f;
    glm::vec3 lightPosition(x, 10.0f, z);
    glm::vec3 sceneCenter(0.0f, 0.0f, 0.0f);

    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 64.0f);

    shadowMap->SetupLightSpaceMatrix(lightProjection, lightPosition, sceneCenter);

    // Activate shader program and set common uniforms outside the loop
    glUseProgram(children[0]->shaderProgram);
    glUniform3fv(glGetUniformLocation(children[0]->shaderProgram, "lightPosition"), 1, glm::value_ptr(lightPosition));
    glUniformMatrix4fv(glGetUniformLocation(children[0]->shaderProgram, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(shadowMap->GetLightSpaceMatrix()));

    // 2. Bind framebuffer and render depth map from light's perspective
    shadowMap->BindFramebuffer();

    glm::mat4 lightViewMatrix = glm::lookAt(lightPosition, sceneCenter, glm::vec3(0.0f, 1.0f, 0.0f));

    for (Mesh* mesh : children) {
        mesh->render(lightViewMatrix, lightProjection, deltaTime);
    }

    glUniform1i(glGetUniformLocation(children[0]->shaderProgram, "shadowMap"), 0);

    for (Mesh* mesh : children) {
        mesh->render(lightViewMatrix, lightProjection, deltaTime);
    }

    ShadowMap::UnbindFramebuffer();

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, shadowMap->GetDepthMap());

    glUniform1i(glGetUniformLocation(children[0]->shaderProgram, "shadowMap"), 1);

    // 3. Render the scene from the camera's perspective
    for (Mesh* mesh : children) {
        mesh->render(view, projection, deltaTime);
    }
}