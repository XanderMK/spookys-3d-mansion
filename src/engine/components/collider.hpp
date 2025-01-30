#pragma once

#include "3ds.h"
#include "citro3d.h"
#include "component.hpp"
#include "gameobject.hpp"
#include <vector>
#include <memory>

class Collider : public Component
{
    public:
        Collider(GameObject *parent) : Component(parent) {};
        ~Collider() = default;

        void Update(float deltaTime) override {};
        void Render() override {};

        virtual bool IsColliding() = 0;
        virtual bool IsColliding(std::shared_ptr<Collider> other) = 0;

        static std::vector<std::shared_ptr<Collider> > sceneColliders;
};

class AABBCollider : public Collider
{
    public:
        AABBCollider(GameObject *parent) : Collider(parent) {};
        AABBCollider(GameObject *parent, C3D_FVec bounds) : Collider(parent), bounds(bounds) {};
        ~AABBCollider() = default;

        void Update(float deltaTime) override {};
        void Render() override {};

        bool IsColliding() override;
        bool IsColliding(std::shared_ptr<Collider> other) override;

        C3D_FVec bounds;
};