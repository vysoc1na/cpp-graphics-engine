#include <Core/Renderer.h>
#include <Core/Shader.h>
#include <Core/Geometry/CubeGeometry.h>

int main() {
    Renderer renderer(glm::ivec2(800, 600));
    Shader shader;
    auto *shadowMap = new ShadowMap(800, 600);
    Scene scene;
    Camera camera(glm::vec3(0.0f, 1.0f, 5.0f), renderer.getResolution());

    scene.children.push_back(
        new Mesh(
            new CubeGeometry(
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f, 1.0f, 1.0f)
            ),
            new Material(
                glm::vec3(1.0f, 0.0f, 0.0f),
                1.0f
            ),
            shader.getShaderProgram(),
            shader.getShaderProgramShadows()
        )
    );

    scene.children.push_back(
        new Mesh(
            new CubeGeometry(
                    glm::vec3(0.0f, -0.5f, 0.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(5.0f, 0.1f, 5.0f)
            ),
            new Material(
                glm::vec3(1.0f, 1.0f, 1.0f),
                1.0f
            ),
            shader.getShaderProgram(),
            shader.getShaderProgramShadows()
        )
    );

    renderer.run(camera, scene, shadowMap);
}