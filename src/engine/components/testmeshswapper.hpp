#pragma once

#include <3ds.h>
#include <memory>

#include "component.hpp"
#include "mesh.hpp"
#include "gameobject.hpp"
#include "core.hpp"

class TestMeshSwapper : public Component
{
    public:
        TestMeshSwapper(GameObject *parent);
        ~TestMeshSwapper() = default;

        void Update(float deltaTime) override;
        void Render() override {};
    private:
        bool currentMesh = false;
        std::shared_ptr<Mesh> meshComponent;
};