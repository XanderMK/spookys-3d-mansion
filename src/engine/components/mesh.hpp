#pragma once

#include <3ds.h>
#include <citro3d.h>
#include <array>
#include <string>

#include "component.hpp"
#include "objload.h"

struct Vertex
{
    std::array<float, 3> positions;
    std::array<float, 2> texCoords;
    std::array<float, 3> normals;
};

class Mesh : public Component
{
    public:
        Mesh(GameObject *parent) : Component(parent) {};
        Mesh(GameObject *parent, const void* vertexData, size_t vertexDataSize);
        Mesh(GameObject *parent, std::string &filename);
        Mesh(const Mesh& other);
        ~Mesh();

        void Update(float deltaTime) override;
        void Render() override;

        void SetVBO(const void* vertexData, size_t vertexDataSize);
        void SetVBO(std::string &filename);
    private:
        void* vbo = nullptr;
        size_t vertexDataSize = 0;
};