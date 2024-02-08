#include <Core/Renderer.h>
#include <Core/Shader.h>
#include <Core/Geometry/CubeGeometry.h>

int main() {
    Renderer renderer(glm::ivec2(800, 600));
    Shader shader;
    Scene scene;

    Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), renderer.getResolution());

    scene.children.push_back(
        new Mesh(
            new CubeGeometry(
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f, 1.0f, 1.0f)
            ),
            new Material(
                glm::vec3(0.1f, 0.8f, 0.7f),
                1.0f
            ),
            shader.getShaderProgram()
        )
     );

    // rendering at 50fps
    // 1681 unique objects + 1681 shader programs
    /*
    for (int x = 0; x < 41; x++) {
        for (int y = 0; y < 41; y++) {
            scene.children.push_back(
                new Mesh(
                    new CubeGeometry(
                        glm::vec3(x - 20, y - 20, -50.0f),
                        glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(0.5f, 0.5f, 0.5f)
                    ),
                    new Material(
                        glm::vec3(1.0f, 1.0f, 1.0f),
                        1.0f
                    )
                )
            );
        }
    }
     */

    renderer.run(camera, scene);
}