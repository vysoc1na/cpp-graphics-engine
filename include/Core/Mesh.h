#ifndef CORE_MESH_H
#define CORE_MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <Core/Geometry.h>
#include <Core/Material.h>

class Mesh {
public:
    Mesh(Geometry *geometry, Material *material, GLuint shaderProgram);
    ~Mesh();

    void render(glm::mat4 view, glm::mat4 projection, float deltaTime);

    Geometry* geometry;
    Material* material;
    GLuint shaderProgram;

private:
    GLuint vao {}, vbo {}, ebo {};

    glm::mat4 model {};

    void setupModelMatrix();
    void setupVertexData();
};

#endif // CORE_MESH_H