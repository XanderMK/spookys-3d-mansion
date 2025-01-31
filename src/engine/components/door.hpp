#pragma once

#include "component.hpp"

class Door : public Component
{
    public:
        Door(GameObject *parent) : Component(parent) { };
        ~Door() = default;

        void Update(float deltaTime) override {};
        void Render() override {};
};