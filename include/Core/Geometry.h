#ifndef CORE_GEOMETRY_H
#define CORE_GEOMETRY_H

#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Geometry {
public:
    Geometry(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    ~Geometry();

    virtual void setupVertices() = 0;
    virtual void setupIndices() = 0;
    // virtual void setupNormals() = 0;

    glm::vec3 getPosition() {
        return position;
    }
    glm::vec3 getRotation() {
        return rotation;
    }
    glm::vec3 getScale() {
        return scale;
    }
    std::vector<GLfloat> getVertices() {
        return vertices;
    }
    std::vector<GLint> getIndices() {
        return indices;
    }
    // std::vector<GLfloat> getNormals() {
    //     return normals;
    // }

    void setPosition(glm::vec3 newPosition) {
        position = newPosition;
    }
    void setRotation(glm::vec3 newRotation) {
        rotation = newRotation;
    }
    void setScale(glm::vec3 newScale) {
        scale = newScale;
    }

private:
    glm::vec3 position {};
    glm::vec3 rotation {};
    glm::vec3 scale {};

protected:
    std::vector<GLfloat> vertices;
    std::vector<GLint> indices;
    // std::vector<GLfloat> normals;
};

#endif // CORE_GEOMETRY_H