#pragma once

#include <3ds.h>
#include <citro3d.h>
#include <tex3ds.h>
#include <iostream>
#include <string>
#include <memory>
#include <map>

#include "model.hpp"

namespace Resources
{
    const std::shared_ptr<C3D_Tex> GetTexture(std::string filename);
    const std::shared_ptr<Model> GetModel(std::string filename);
    void ClearResources();
    
    extern std::map<std::string, std::shared_ptr<C3D_Tex>> textures;
    extern std::map<std::string, std::shared_ptr<Model>> models;

    extern std::vector<std::shared_ptr<C3D_Tex>> textureVec;
    extern std::vector<std::shared_ptr<Model>> modelVec;
};