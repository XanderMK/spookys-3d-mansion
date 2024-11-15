#pragma once

#include <3ds.h>

#include "component.hpp"
#include "gameobject.hpp"
#include "transform.hpp"

class Camera : public Component
{
    public:
        Camera(int uLoc_view);
        ~Camera();

        void Update(float deltaTime) override;
        void Render() override {}

        int updatePriority = 5;

        C3D_Mtx GetCameraMatrix();
    private:
        int uLoc_view;
        C3D_Mtx cameraMatrix;
};