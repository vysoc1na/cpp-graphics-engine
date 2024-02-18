#include <filesystem>
#include <Core/Renderer.h>
#include <Core/Shader.h>
#include <Core/Geometry/ReferenceGeometry.h>
#include <Core/Geometry/CubeGeometry.h>
#include <Loaders/OBJLoader.h>

int main() {
    std::filesystem::path workspace = std::filesystem::current_path();

    std::filesystem::path defaultVertexShader = workspace / "../source/shaders/default.vert";
    std::filesystem::path defaultFragmentShader = workspace / "../source/shaders/default.frag";

    Renderer renderer(glm::ivec2(800, 600));
    auto *shader = new Shader(
        defaultVertexShader.c_str(),
        defaultFragmentShader.c_str()
    );
    Scene scene;
    Camera camera(glm::vec3(0.0f, 1.0f, 5.0f), renderer.getResolution());

    auto *shadowMap = new ShadowMap(800, 600);

    auto *loader = new OBJLoader();
    loader->load("icosphere", "objects/icosphere/icosphere.obj");

    OBJ* icosphere = loader->getByName("icosphere");

    scene.children.push_back(
        new Mesh(
            new ReferenceGeometry(
                icosphere->vertices,
                icosphere->indices,
                icosphere->normals,
                glm::vec3(1.0f, -0.5f, 0.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(1.0f, 1.0f, 1.0f)
            ),
            new Material(
                glm::vec3(0.0f, 0.0f, 1.0f),
                1.0f
            ),
            shader->getShaderProgram()
        )
    );

    scene.children.push_back(
        new Mesh(
            new CubeGeometry(
                    glm::vec3(-1.0f, 0.0f, 0.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f, 1.0f, 1.0f)
            ),
            new Material(
                glm::vec3(1.0f, 0.0f, 0.0f),
                1.0f
            ),
            shader->getShaderProgram()
        )
    );

    scene.children.push_back(
        new Mesh(
            new CubeGeometry(
                    glm::vec3(0.0f, -1.0f, 0.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(50.0f, 1.0f, 50.0f)
            ),
            new Material(
                glm::vec3(1.0f, 1.0f, 1.0f),
                1.0f
            ),
            shader->getShaderProgram()
        )
    );

    renderer.run(camera, scene, shadowMap);
}