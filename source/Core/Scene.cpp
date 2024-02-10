#include <iostream>
#include <Core/Scene.h>

Scene::Scene() = default;

Scene::~Scene() = default;

void Scene::update(glm::mat4 view, glm::mat4 projection, ShadowMap* shadowMap, float deltaTime) {
    // 1. Set up light position and scene center
    glm::vec3 lightPosition(10.0f, 5.0f, 10.0f);
    glm::vec3 sceneCenter(0.0f, 0.0f, 0.0f);

    shadowMap->SetupLightSpaceMatrix(projection, lightPosition, sceneCenter);

    // 2. Bind framebuffer and render depth map from light's perspective
    shadowMap->BindFramebuffer();

    // Activate shader program and set common uniforms outside the loop
    glUseProgram(children[0]->shaderProgram);

    for (Mesh* mesh : children) {
        glm::mat4 lightViewMatrix = glm::lookAt(lightPosition, sceneCenter, glm::vec3(0.0f, 1.0f, 0.0f));

        mesh->render(lightViewMatrix, projection, deltaTime);
    }

    ShadowMap::UnbindFramebuffer();

    // Bind shadow map texture to a texture unit (e.g., GL_TEXTURE1)
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, shadowMap->GetDepthMap());

    glUseProgram(children[0]->shaderProgram);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Set the shadow map texture unit in your shader
    glUniformMatrix4fv(glGetUniformLocation(children[0]->shaderProgram, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(shadowMap->GetLightSpaceMatrix()));
    glUniform1i(glGetUniformLocation(children[0]->shaderProgram, "shadowMap"), 1);

    glClear(GL_DEPTH_BUFFER_BIT);

    // 3. Render the scene from the camera's perspective
    for (Mesh* mesh : children) {
        mesh->render(view, projection, deltaTime);
    }

    // Deactivate shader program
    glUseProgram(0);
}