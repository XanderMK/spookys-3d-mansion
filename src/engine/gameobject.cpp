#include "gameobject.hpp"
#include "mesh.hpp"

GameObject::GameObject()
{
    this->transform = AddComponent<Transform>();
}

GameObject::~GameObject() = default;

void GameObject::Update()
{
    for (unsigned int i = 0; i < this->components.size(); i++)
    {
        this->components[i]->Update();
    }
}

void GameObject::Render()
{
    // Set matrix to conform to object transform

    // Render all meshes
    std::vector<std::shared_ptr<Mesh> > meshes = this->GetComponents<Mesh>();
    for (auto mesh : meshes)
    {
        mesh->Render();
    }
}