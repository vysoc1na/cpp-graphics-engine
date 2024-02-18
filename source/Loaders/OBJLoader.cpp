#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <utility>
#include <Loaders/OBJLoader.h>

OBJLoader::OBJLoader() = default;

OBJLoader::~OBJLoader() = default;

void OBJLoader::load(std::string name, const std::string& path) {
    std::filesystem::path workspace = std::filesystem::current_path();
    std::filesystem::path filePath = workspace / ".." / path;

    std::ifstream objFile(filePath);
    if (!objFile.is_open()) {
        std::cerr << "Error: Unable to open Object file - " << filePath << std::endl;
        std::exit(-1);
    }

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> indices;
    std::vector<glm::vec3> normals;

    std::string line;
    while (std::getline(objFile, line)) {
        // vertices
        if (line.substr(0, 2) == "v ") {
            glm::vec3 vertex;
            sscanf(line.c_str(), "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
            vertices.push_back(vertex);
        }
        // indices
        if (line.substr(0, 2) == "f ") {
            glm::vec3 index;
            sscanf(line.c_str(), "f %f/%*d/%*d %f/%*d/%*d %f/%*d/%*d", &index.x, &index.y, &index.z);
            indices.push_back(index);
        }

        // normals
        if (line.substr(0, 2) == "vn") {
            glm::vec3 normal;
            sscanf(line.c_str(), "v %f %f %f", &normal.x, &normal.y, &normal.z);
            normals.push_back(normal);
        }
    }

    OBJ* object = new OBJ(std::move(name), vertices, indices, normals);

    models.push_back(object);

    std::cout << "Loaded model: " << models[0]->name << std::endl;
}

OBJ* OBJLoader::getByName(const std::string& name) {
    for (OBJ* obj : models) {
        if (obj->name == name) {
            return obj;
        }
    }

    return nullptr;
}