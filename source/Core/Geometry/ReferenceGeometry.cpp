#include <Core/Geometry/ReferenceGeometry.h>

ReferenceGeometry::ReferenceGeometry(
    std::vector<glm::vec3> &inputVertices,
     std::vector<glm::vec3> &inputIndices,
     std::vector<glm::vec3> &inputNormals,
     glm::vec3 inputPosition,
     glm::vec3 inputRotation,
     glm::vec3 inputScale
 ) : Geometry(inputPosition, inputRotation, inputScale) {
    for (glm::vec3 vertex : inputVertices) {
        vertices.push_back(vertex.x);
        vertices.push_back(vertex.y);
        vertices.push_back(vertex.z);
    }

    for (glm::vec3 index : inputIndices) {
        indices.push_back(index.x - 1.0f);
        indices.push_back(index.y - 1.0f);
        indices.push_back(index.z - 1.0f);
    }

    for (glm::vec3 normal : inputNormals) {
        normals.push_back(normal.x);
        normals.push_back(normal.y);
        normals.push_back(normal.z);
    }
}


void ReferenceGeometry::setupVertices() {}

void ReferenceGeometry::setupNormals() {}

void ReferenceGeometry::setupIndices() {}