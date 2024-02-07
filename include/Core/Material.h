#ifndef CORE_MATERIAL_H
#define CORE_MATERIAL_H

#include <glm/glm.hpp>

class Material {
public:
    Material(glm::vec3 inputColor, float inputAlpha);
    ~Material();

    glm::vec3 getColor() {
        return color;
    }
    float getAlpha() {
        return alpha;
    }

    void setColor(glm::vec3 newColor) {
        color = newColor;
    }
    void setAlpha(float newAlpha) {
        alpha = newAlpha;
    }

private:
    glm::vec3 color {};
    float alpha;
};

#endif // CORE_MATERIAL_H