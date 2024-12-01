#include "mesh.hpp"
#include <iostream>

Mesh::Mesh(GameObject *parent, const void* vertexData, size_t vertexDataSize) : Component(parent)
{
    this->SetVBO(vertexData, vertexDataSize);
}

Mesh::Mesh(GameObject *parent, std::string &filename) : Component(parent)
{
    this->SetVBO(filename);
}

Mesh::Mesh(const Mesh& other) : Component(other.parent)
{
    this->SetVBO(other.vbo, other.vertexDataSize);
}

Mesh::~Mesh()
{
    if (this->vbo != nullptr)
        linearFree(this->vbo);
}

void Mesh::Update(float deltaTime) {};

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

void Mesh::SetVBO(std::string &filename)
{
    // Release VBO if allocated
    if (this->vbo != nullptr)
        linearFree(this->vbo);

    // Load model from file
    obj::Model model = obj::loadModelFromFile(filename);

    const size_t faceIndexCount = model.faces["default"].size();

    // Get all vertices from file
    std::vector<float> vertices;
    vertices.reserve(faceIndexCount * 8);
    for (size_t i = 0; i < faceIndexCount; i++)
    {
        vertices.push_back(model.vertex[model.faces["default"][i] * 3 + 0]);
        vertices.push_back(model.vertex[model.faces["default"][i] * 3 + 1]);
        vertices.push_back(model.vertex[model.faces["default"][i] * 3 + 2]);

        vertices.push_back(model.texCoord[model.faces["default"][i] * 2 + 0]);
        vertices.push_back(model.texCoord[model.faces["default"][i] * 2 + 1]);

        vertices.push_back(model.normal[model.faces["default"][i] * 3 + 0]);
        vertices.push_back(model.normal[model.faces["default"][i] * 3 + 1]);
        vertices.push_back(model.normal[model.faces["default"][i] * 3 + 2]);
    }

    // Allocate VBO
    this->vbo = linearAlloc(faceIndexCount * sizeof(Vertex));
    this->vertexDataSize = faceIndexCount;

    // Copy from vector to VBO
    memmove(this->vbo, vertices.data(), vertices.size() * sizeof(float));
}