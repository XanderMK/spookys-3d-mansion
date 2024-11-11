#pragma once

#include "component.hpp"
#include "transform.hpp"

class Camera : public Component
{
    public:
        Camera();
        ~Camera();

        void Update() override;
    private:
        C3D_Mtx cameraMatrix;
};