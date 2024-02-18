#ifndef LOADERS_OBJLOADER_H
#define LOADERS_OBJLOADER_H

#include <Loaders/OBJ.h>
class OBJLoader {
public:
    OBJLoader();
    ~OBJLoader();

    void load(std::string name, const std::string& path);

    OBJ* getByName(const std::string& name);

private:
    std::vector<OBJ*> models;
};

#endif // LOADERS_OBJLOADER_H