#include "mesh.hpp"

Mesh::Mesh(void* vertexData, size_t vertexDataSize)
{
    this->SetVBO(vertexData, vertexDataSize);
}

Mesh::~Mesh()
{
    if (this->vbo != nullptr)
        linearFree(this->vbo);
}

void Mesh::Render()
{
    C3D_DrawArrays(GPU_TRIANGLES, 0, vertexDataSize);
}

void Mesh::SetVBO(void* vertexData, size_t vertexDataSize)
{
    // Release VBO if allocated
    if (this->vbo != nullptr)
        linearFree(this->vbo);

    // Allocate VBO
    this->vbo = linearAlloc(vertexDataSize);
    this->vertexDataSize = vertexDataSize;

    // Copy vertex data to VBO
    memcpy(vertexData, this->vbo, vertexDataSize);
}