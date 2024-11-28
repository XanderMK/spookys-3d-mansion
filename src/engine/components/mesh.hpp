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
        Mesh(GameObject *parent) : Component(parent) {};
        Mesh(GameObject *parent, const void* vertexData, size_t vertexDataSize);
        Mesh(const Mesh& other);
        ~Mesh();

        void Update(float deltaTime) override;
        void Render() override;

        void SetVBO(const void* vertexData, size_t vertexDataSize);
    private:
        void* vbo = nullptr;
        size_t vertexDataSize = 0;
};