#pragma once

#include <vector>

#include "gameobject.hpp"

struct Scene
{
    std::vector<std::shared_ptr<GameObject> > gameObjects;
};