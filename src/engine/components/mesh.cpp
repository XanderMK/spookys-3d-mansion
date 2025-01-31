#include "mesh.hpp"

Mesh::Mesh(GameObject *parent, std::string &filename) : Component(parent), filename(filename)
{
}

Mesh::~Mesh() {}

void Mesh::Update(float deltaTime) 
{
    if (this->model == nullptr)
        this->model = Resources::GetModel(filename);
};

void Mesh::Render()
{
    for (auto &submesh : this->model->submodels)
    {
        // Set material
        C3D_LightEnvMaterial(&Global::lightEnvironment, &submesh->mat);

        // Bind texture
        auto textureComponent = this->parent->GetComponent<Texture>();
        if (textureComponent != nullptr)
            C3D_TexBind(0, textureComponent->texture.get());
        else
            C3D_TexBind(0, submesh->tex.get());

        // Configure buffer
        C3D_BufInfo* bufInfo = C3D_GetBufInfo();
        BufInfo_Init(bufInfo);
        BufInfo_Add(bufInfo, submesh->vbo, sizeof(Vertex), 3, 0x210);

        // Draw
        C3D_DrawElements(GPU_TRIANGLES, submesh->iboSize, C3D_UNSIGNED_SHORT, submesh->ibo);
    }
}