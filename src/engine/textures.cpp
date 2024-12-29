#include "textures.hpp"
#include <iostream>

std::map<std::string, std::shared_ptr<C3D_Tex>> Textures::textures;

std::shared_ptr<C3D_Tex> Textures::GetTexture(std::string filename)
{
    // If texture is not loaded, load it
    if (Textures::textures.find(filename) == Textures::textures.end())
    {
        // Init texture
        auto newTex = std::make_shared<C3D_Tex>();

        // Get texture filename as it will exist in RomFS
        std::string realFilename = filename.substr(0, filename.find('.')) + ".t3x";

        // Load from file
        FILE *file = fopen(("romfs:/gfx/" + realFilename).c_str(), "rb");

        auto result = Tex3DS_TextureImportStdio(file, newTex.get(), nullptr, true);
        if (!result)
            exit(1);

        Tex3DS_TextureFree(result);
        fclose(file);

        C3D_TexSetFilter(newTex.get(), GPU_LINEAR, GPU_NEAREST);
        C3D_TexSetWrap(newTex.get(), GPU_REPEAT, GPU_REPEAT);

        // Push new texture to map
        Textures::textures.insert(std::pair(filename, newTex));
    }

    // Texture is now guaranteed to be loaded; send it
    return Textures::textures[filename];
}

void Textures::ClearTextures()
{
    Textures::textures.clear();
}