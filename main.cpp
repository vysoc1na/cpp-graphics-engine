#include <Core/Renderer.h>
#include <Core/Shader.h>
#include <Core/Geometry/CubeGeometry.h>

const char* vertexShaderSource = R"(
    #version 330 core

    layout (location = 0) in vec3 position;
    layout (location = 1) in vec3 normal;

    out vec4 FragPos;
    out vec3 FragNormal;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main() {
        FragPos = model * vec4(position, 1.0);
        FragNormal = mat3(transpose(inverse(model))) * normal;

        gl_Position = projection * view * model * vec4(position, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 330 core

    out vec4 FragColor;
    in vec3 FragNormal;
    in vec4 FragPos;

    uniform vec3 color;
    uniform float alpha;
    uniform float enableColors;
    uniform vec3 lightPosition;

    // uniform sampler2DShadow shadowMap;
    uniform sampler2D shadowMap;
    uniform mat4 lightSpaceMatrix;

    float getShadow() {
        vec4 lightView_Position = lightSpaceMatrix * FragPos * 0.5 + 0.5;

        float dotLightNormal = max(dot(FragNormal, normalize(lightPosition - FragPos.xyz)), 0.1);
        float bias = max(0.0005 * (1 - dotLightNormal), 0.0001);

        float shadow = texture(shadowMap, lightView_Position.xy).r;

        if (lightView_Position.z > 1.0) {
            lightView_Position.z = 1.0;
        }

        return (shadow + bias) < lightView_Position.z ? 0.3 : 1.0;
    }

    vec3 getLighting() {
        float ambientStrength = 0.8;
        float diffuseStrength = max(dot(FragNormal, normalize(lightPosition - FragPos.xyz)), 0.0);
        vec3 ambient = ambientStrength * color.rgb;
        vec3 diffuse = diffuseStrength * color.rgb;

        return ambient + diffuse;
    }

    void main() {
        vec3 lighting = getLighting();
        float shadow = getShadow();

        FragColor = vec4(lighting * shadow, alpha);
    }
)";

int main() {
    Renderer renderer(glm::ivec2(800, 600));
    auto *shader = new Shader(
        vertexShaderSource,
        fragmentShaderSource
    );
    Scene scene;
    Camera camera(glm::vec3(0.0f, 3.0f, 5.0f), renderer.getResolution());

    auto *shadowMap = new ShadowMap(800, 600);

    scene.children.push_back(
        new Mesh(
            new CubeGeometry(
                    glm::vec3(-2.0f, 0.0f, 0.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(1.0f, 1.0f, 1.0f)
            ),
            new Material(
                glm::vec3(0.0f, 1.0f, 0.0f),
                1.0f
            ),
            shader->getShaderProgram()
        )
    );
    scene.children.push_back(
        new Mesh(
            new CubeGeometry(
                    glm::vec3(3.0f, 1.0f, 1.0f),
                    glm::vec3(0.0f, 45.0f, 0.0f),
                    glm::vec3(1.0f, 3.0f, 1.0f)
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
                    glm::vec3(2.0f, 0.0f, 0.0f),
                    glm::vec3(0.0f, -45.0f, 0.0f),
                    glm::vec3(1.0f, 1.0f, 4.0f)
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
                    glm::vec3(0.0f, -1.0f, 0.0f),
                    glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(10.0f, 1.0f, 10.0f)
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
to play with a shadow map size, from small **512x512** to very large **4096x4096**, and nothing seemed to help this issue;