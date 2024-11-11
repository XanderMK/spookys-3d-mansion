#pragma once

#include <3ds.h>
#include <citro3d.h>
#include <array>

#include "component.hpp"

struct Vertex
{
    std::array<float, 3> positions;
    std::array<float, 2> texCoords;
    std::array<float, 3> normals;
};

class Mesh : public Component
{
    public:
        Mesh();
        Mesh(void* vertexData, size_t vertexDataSize);
        ~Mesh();

        void Render() override;

        void SetVBO(void* vertexData, size_t vertexDataSize);
    private:
        void* vbo = nullptr;
        size_t vertexDataSize = 0;
};