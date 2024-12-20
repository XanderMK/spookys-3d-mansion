#pragma once

#include <3ds.h>
#include <citro3d.h>

#include "component.hpp"
#include "gameobject.hpp"

class Camera : public Component
{
    public:
        Camera(GameObject *parent, int uLoc_view);
        ~Camera() = default;

        void Update(float deltaTime) override;
        void Render() override {}

        int updatePriority = 5;
    private:
        int uLoc_view;
};