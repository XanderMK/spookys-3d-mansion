#pragma once

#include <3ds.h>
#include <citro3d.h>
#include "ufbx.h"
#include <vector>
#include <memory>

struct Vertex
{
    ufbx_vec3 position;
    ufbx_vec3 normal;
    ufbx_vec2 uv;
};

struct Submodel
{
    Vertex *vbo = nullptr;
    int vboSize = 0;

    unsigned short *ibo = nullptr;
    int iboSize = 0;

    std::shared_ptr<C3D_Tex> tex;
    C3D_Material mat{};

    ~Submodel()
    {
        if (this->vbo != nullptr)
            linearFree(this->vbo);
        if (this->ibo != nullptr)
            linearFree(this->ibo);
    }
};

struct Model
{
    void ConvertModelPart(std::shared_ptr<Submodel> &submodel, const ufbx_mesh &mesh, const ufbx_mesh_part &part);
    void SetSubmodelMaterial(std::shared_ptr<Submodel> &submodel, ufbx_material &mat);

    std::vector<std::shared_ptr<Submodel>> submodels;
};