#include "testmeshswapper.hpp"

TestMeshSwapper::TestMeshSwapper(GameObject *parent) : Component(parent)
{
    this->meshComponent = this->parent->GetComponent<Mesh>();
}

void TestMeshSwapper::Update(float deltaTime)
{
    this->currentMesh = !this->currentMesh;
    if (this->currentMesh)
    {
        meshComponent->SetVBO(reinterpret_cast<const void*>(cubeMesh), cubeMeshListSize);
    }
    else
    {
        meshComponent->SetVBO(reinterpret_cast<const void*>(vertexList), vertexListSize);
    }
}