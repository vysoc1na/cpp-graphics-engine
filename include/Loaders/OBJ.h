#ifndef LOADERS_OBJ_H
#define LOADERS_OBJ_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

class OBJ {
public:
    OBJ(std::string name, std::vector<glm::vec3> vertices, std::vector<glm::vec3> indices, std::vector<glm::vec3> normals);
    ~OBJ();

    std::string name;

    std::vector<glm::vec3> vertices {};
    std::vector<glm::vec3> indices {};
    std::vector<glm::vec3> normals {};
};

#endif // LOADERS_OBJ_H