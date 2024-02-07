#include <Core/Material.h>

Material::Material(glm::vec3 inputColor, float inputAlpha) {
    color = inputColor;
    alpha = inputAlpha;
}

Material::~Material() = default;