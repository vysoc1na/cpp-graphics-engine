#include <Core/Geometry/CubeGeometry.h>

CubeGeometry::CubeGeometry(glm::vec3 inputPosition, glm::vec3 inputRotation, glm::vec3 inputScale)
        : Geometry(inputPosition, inputRotation, inputScale) {}

void CubeGeometry::setupVertices() {
    vertices = {
        // front
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        // back
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f
    };
}

void CubeGeometry::setupNormals() {
    normals = {
        // front
        0.0f, 0.0f, 1.0f,
        // right
        1.0f, 0.0f, 0.0f,
        // back
        0.0f, 0.0f, -1.0f,
        // left
        -1.0f, 0.0f, 0.0f,
        // bottom
        0.0f, -1.0f, 0.0f,
        // top
        0.0f, 1.0f, 0.0f
    };
}

void CubeGeometry::setupIndices() {
    indices = {
        // front
        0, 1, 2, 2, 3, 0,
        // right
        1, 5, 6, 6, 2, 1,
        // back
        7, 6, 5, 5, 4, 7,
        // left
        4, 0, 3, 3, 7, 4,
        // bottom
        4, 5, 1, 1, 0, 4,
        // top
        3, 2, 6, 6, 7, 3
    };
}