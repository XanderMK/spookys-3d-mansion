#include "resources.hpp"

std::map<std::string, std::shared_ptr<C3D_Tex>> Resources::textures;
std::map<std::string, std::shared_ptr<Model>> Resources::models;

const std::shared_ptr<C3D_Tex> Resources::GetTexture(std::string filename)
{
    // If texture is not loaded, load it
    if (textures.find(filename) == textures.end())
    {
        // Init texture
        auto newTex = std::make_shared<C3D_Tex>();

        // Get texture filename as it will exist in RomFS
        std::string realFilename = filename.substr(0, filename.find('.')) + ".t3x";

        // Load from file
        FILE *file = fopen(("romfs:/gfx/" + realFilename).c_str(), "rb");

        auto result = Tex3DS_TextureImportStdio(file, newTex.get(), nullptr, true);
        if (!result)
        {
            std::cout << "Failed to load texture " << filename << "!\n";
            return nullptr;
        }

        Tex3DS_TextureFree(result);
        fclose(file);

        C3D_TexSetFilter(newTex.get(), GPU_LINEAR, GPU_LINEAR);
        C3D_TexSetWrap(newTex.get(), GPU_REPEAT, GPU_REPEAT);

        // Push new texture to map
        textures.insert(std::pair(filename, newTex));
    }

    // Texture is now guaranteed to be loaded; send it
    return textures.at(filename);
}

const std::shared_ptr<Model> Resources::GetModel(std::string filename)
{
    // If model is not loaded, load it
    if (models.find(filename) == models.end())
    {
        std::shared_ptr<Model> newModel = std::make_shared<Model>();

        // Load model from file
        ufbx_load_opts opts{};
        opts.target_axes = ufbx_axes_right_handed_y_up;
        opts.target_unit_meters = 0.1f;

        ufbx_error error;
        ufbx_scene *scene = ufbx_load_file(filename.c_str(), &opts, &error);
        if (!scene)
        {
            std::cout << "Error opening file: " << filename << ": " << error.description.data << std::endl;
            return nullptr;
        }

        for (auto &mesh : scene->meshes)
        {
            for (unsigned int i = 0; i < mesh->material_parts.count; i++)
            {
                auto submodel = std::make_shared<Submodel>();

                newModel->ConvertModelPart(submodel, *mesh, mesh->material_parts[i]);
                
                std::string texFilename(mesh->materials[i]->textures[0].texture->absolute_filename.data);
                texFilename = texFilename.substr(texFilename.find_last_of('/') + 1);
                submodel->tex = GetTexture(texFilename);

                newModel->SetSubmodelMaterial(submodel, *mesh->materials[i]);

                newModel->submodels.push_back(submodel);
            }
        }

        ufbx_free_scene(scene);

        models.insert(std::pair(filename, newModel));
    }

    // Model is now guaranteed to be loaded; send it
    return models.at(filename);
}

void Resources::ClearResources()
{
    // Delete all models (they deallocate themselves)
    models.clear();

    // Delete all textures
    for (auto itr = textures.begin(); itr != textures.end(); itr++)
    {
        C3D_TexDelete(itr->second.get());
    }
    textures.clear();
}