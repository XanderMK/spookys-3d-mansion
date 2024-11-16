#pragma once

#include <3ds.h>

#include "component.hpp"
#include "gameobject.hpp"
#include "transform.hpp"
#include "input.hpp"

class FreeCam : public Component
{
    public:
        FreeCam();
        ~FreeCam();

        void Update(float deltaTime) override;
        void Render() override {}
    private:
        static constexpr float sensitivity = 180.0f;
        static constexpr float moveSpeed = 3.0f;
};