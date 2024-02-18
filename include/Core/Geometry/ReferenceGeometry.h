#ifndef CORE_GEOMETRY_REFERENCE_H
#define CORE_GEOMETRY_REFERENCE_H

#include <vector>
#include <Core/Geometry.h>

class ReferenceGeometry : public Geometry {
public:
    ReferenceGeometry(
        std::vector<glm::vec3> &vertices,
        std::vector<glm::vec3> &indices,
        std::vector<glm::vec3> &normals,
        glm::vec3 inputPosition,
        glm::vec3 inputRotation,
        glm::vec3 inputScale
    );
    ~ReferenceGeometry() = default;

    void setupVertices() override;
    void setupNormals() override;
    void setupIndices() override;
};

#endif // CORE_GEOMETRY_REFERENCE_H