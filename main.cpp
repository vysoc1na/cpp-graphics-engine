#include <Core/Renderer.h>
#include <Core/Geometry/CubeGeometry.h>

int main() {
    Renderer renderer(glm::ivec2(800, 600));
    Scene scene;

    Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), renderer.getResolution());

    CubeGeometry geometry(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    );
    Material material(
        glm::vec3(1.0f, 1.0f, 1.0f),
        1.0f
    );
    Mesh mesh(&geometry, &material);

    scene.add(mesh);
    renderer.run(camera, scene);
}