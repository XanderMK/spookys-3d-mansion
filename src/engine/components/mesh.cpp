#include "mesh.hpp"
#include <iostream>

Mesh::Mesh(const void* vertexData, size_t vertexDataSize)
{
    this->SetVBO(vertexData, vertexDataSize);
}

Mesh::Mesh(const Mesh& other)
{
    this->SetVBO(other.vbo, other.vertexDataSize);
}

Mesh::~Mesh()
{
    if (this->vbo != nullptr)
        linearFree(this->vbo);
}

void Mesh::Update() {};

void Mesh::Render()
{
    // Configure buffer
	C3D_BufInfo* bufInfo = C3D_GetBufInfo();
	BufInfo_Init(bufInfo);
	BufInfo_Add(bufInfo, this->vbo, sizeof(Vertex), 3, 0x210);

    // Draw
    C3D_DrawArrays(GPU_TRIANGLES, 0, this->vertexDataSize);
}

void Mesh::SetVBO(const void* vertexData, size_t vertexDataSize)
{
    // Release VBO if allocated
    if (this->vbo != nullptr)
        linearFree(this->vbo);

    // Allocate VBO
    this->vbo = linearAlloc(vertexDataSize * sizeof(Vertex));
    this->vertexDataSize = vertexDataSize;

    // Copy vertex data to VBO
    memcpy(this->vbo, vertexData, vertexDataSize * sizeof(Vertex));
}