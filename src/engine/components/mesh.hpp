#pragma once

#include <3ds.h>
#include <citro3d.h>
#include "ufbx.h"
#include <array>
#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include "component.hpp"
#include "textures.hpp"

struct Vertex
{
    ufbx_vec3 position;
    ufbx_vec3 normal;
    ufbx_vec2 uv;
};

struct Submesh
{
    Vertex *vbo = nullptr;
    int vboSize = 0;

    unsigned short *ibo = nullptr;
    int iboSize = 0;

    std::shared_ptr<C3D_Tex> tex;
    C3D_Material mat{};

    ~Submesh()
    {
        if (this->vbo != nullptr)
            linearFree(this->vbo);
        if (this->ibo != nullptr)
            linearFree(this->ibo);
    }
};

class Mesh : public Component
{
    public:
        Mesh(GameObject *parent) : Component(parent) {};
        Mesh(GameObject *parent, std::string &filename);
        ~Mesh();

        void Update(float deltaTime) override;
        void Render() override;

        void SetMesh(const void* vertexData, size_t vertexDataSize);
        void SetMesh(std::string &filename);
    private:
        std::vector<std::shared_ptr<Submesh> > submeshes;
        void ConvertMeshPart(std::shared_ptr<Submesh> &submesh, const ufbx_mesh &mesh, const ufbx_mesh_part &part);
};