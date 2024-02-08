#include <Core/Geometry.h>

Geometry::Geometry(glm::vec3 inputPosition, glm::vec3 inputRotation, glm::vec3 inputScale) {
    position = inputPosition;
    rotation = inputRotation;
    scale = inputScale;
}

Geometry::~Geometry() = default;