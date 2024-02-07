#include <Core/Geometry.h>

Geometry::Geometry(glm::vec3 inputPosition, glm::vec3 inputRotation, glm::vec3 inputScale) {
    position = inputPosition;
    rotation = inputRotation;
    scale = inputScale;

    setupVertices();
    setupIndices();
}

Geometry::~Geometry() = default;

void Geometry::setupVertices() {
    vertices = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f
    };
}

void Geometry::setupIndices() {
    indices = {
        0, 1, 2, 2, 3, 0,   // Front face
        4, 5, 6, 6, 7, 4,   // Back face
        0, 4, 3, 3, 7, 4,   // Left face
        1, 5, 2, 2, 6, 5,   // Right face
        0, 1, 4, 4, 5, 1,   // Bottom face
        2, 3, 6, 6, 7, 3    // Top face
    };
}