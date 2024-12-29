#pragma once

#include <3ds.h>
#include <citro3d.h>
#include <tex3ds.h>
#include <string>
#include <memory>
#include <map>

namespace Textures
{
    std::shared_ptr<C3D_Tex> GetTexture(std::string filename);
    void ClearTextures();
    
    extern std::map<std::string, std::shared_ptr<C3D_Tex>> textures;
};