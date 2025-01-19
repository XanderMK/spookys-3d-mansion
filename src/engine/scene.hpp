#pragma once

#include <vector>
#include <sstream>
#include <fstream>

#include "gameobject.hpp"
#include "camera.hpp"
#include "freecam.hpp"
#include "mesh.hpp"

struct Scene
{
    std::vector<std::shared_ptr<GameObject> > gameObjects;
    Core *core;

    void LoadFromString(std::string in);
    void LoadFromFile(std::string filename);
};