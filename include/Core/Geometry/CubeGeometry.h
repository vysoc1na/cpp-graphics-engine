#ifndef CORE_GEOMETRY_CUBE_H
#define CORE_GEOMETRY_CUBE_H

#include <Core/Geometry.h>

class CubeGeometry : public Geometry {
public:
    CubeGeometry(glm::vec3 inputPosition, glm::vec3 inputRotation, glm::vec3 inputScale);
    ~CubeGeometry() = default;

    void setupVertices() override;
    void setupIndices() override;
};

#endif // CORE_GEOMETRY_CUBE_H