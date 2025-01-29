#pragma once

#include <3ds.h>
#include <citro3d.h>

#include "component.hpp"
#include "gameobject.hpp"
#include "input.hpp"

class FreeCam : public Component
{
    public:
        FreeCam(GameObject *parent);
        ~FreeCam() = default;

        void Update(float deltaTime) override;
        void Render() override {}
    private:
        static constexpr float sensitivity = 180.0f;
        static constexpr float moveSpeed = 3.0f;

        float rotX = 0.f, rotY = 0.f;
};