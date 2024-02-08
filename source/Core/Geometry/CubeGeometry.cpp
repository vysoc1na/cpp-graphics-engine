#include "include/Core/Geometry/CubeGeometry.h"

CubeGeometry::CubeGeometry(glm::vec3 inputPosition, glm::vec3 inputRotation, glm::vec3 inputScale)
        : Geometry(inputPosition, inputRotation, inputScale) {
    setupVertices();
    setupIndices();
}

void CubeGeometry::setupVertices() {
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

void CubeGeometry::setupIndices() {
    indices = {
        0, 1, 2, 2, 3, 0,   // Front face
        4, 5, 6, 6, 7, 4,   // Back face
        0, 4, 3, 3, 7, 4,   // Left face
        1, 5, 2, 2, 6, 5,   // Right face
        0, 1, 4, 4, 5, 1,   // Bottom face
        2, 3, 6, 6, 7, 3    // Top face
    };
}