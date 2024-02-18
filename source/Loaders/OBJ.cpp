#include <Loaders/OBJ.h>

OBJ::OBJ(std::string inputName, std::vector<glm::vec3> v, std::vector<glm::vec3> i, std::vector<glm::vec3> n)
    : name(inputName), vertices(v), indices(i), normals(n) {};

OBJ::~OBJ() = default;