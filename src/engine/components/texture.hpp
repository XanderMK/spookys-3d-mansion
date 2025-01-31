#pragma once

#include <3ds.h>
#include <citro3d.h>

#include "component.hpp"
#include "gameobject.hpp"

class Texture : public Component
{
    public:
        Texture(GameObject *parent, std::shared_ptr<C3D_Tex> texture) : Component(parent), texture(texture) {};
        ~Texture() = default;

        void Update(float deltaTime) override {}
        void Render() override {}

        std::shared_ptr<C3D_Tex> texture;
};