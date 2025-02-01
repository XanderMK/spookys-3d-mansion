#pragma once

#include "3ds.h"
#include "citro3d.h"
#include "gameobject.hpp"
#include "component.hpp"
#include "collider.hpp"
#include "camera.hpp"
#include "door.hpp"

class Player : public Component
{
    public:
        Player(GameObject *parent, float rotX, float rotY);
        ~Player() = default;

        void Update(float deltaTime) override;
        void Render() override {};
    private:
        const float walkSpeed = 3.0f;
        const float runSpeed = 5.0f;

        const C3D_FVec defaultCameraPos = FVec3_New(0.0f, 1.35f, 0.0f);
        const C3D_FVec defaultColliderBounds = FVec3_New(0.6f, 1.7f, 0.6f);

        const float camSensitivity = 180.0f;
        float xRot = 0.0f, yRot = 0.0f;

        const float interactDistance = 2.0f;

        std::shared_ptr<GameObject> playerCam = nullptr;
        std::shared_ptr<AABBCollider> collider = nullptr;
        std::vector<std::shared_ptr<GameObject> > sceneDoors;
};