#include "freecam.hpp"

void FreeCam::Update(float deltaTime)
{
    // Rotation
    static float rotX = 0, rotY = 0;
    
    rotX -= (static_cast<float>(Input::cStick.dy) / 128.0f) * sensitivity * deltaTime;
    rotY += (static_cast<float>(Input::cStick.dx) / 128.0f) * sensitivity * deltaTime;

    // Clamp rotation on X-axis
    if (rotX < -90.0f)
        rotX = -90.0f;
    else if (rotX > 90.0f)
        rotX = 90.0f;
    
    // Reset angle on Y-axis to stay between 0-360
    if (rotY < 0.0f)
        rotY += 360.0f;
    else if (rotY > 360.0f)
        rotY -= 360.0f;

    this->parent->transform->SetRotation(FVec3_New(static_cast<float>(C3D_AngleFromDegrees(rotX)), static_cast<float>(C3D_AngleFromDegrees(rotY)), 0));


    // Movement
    C3D_FVec forward{}, right{}, up{};
    C3D_Mtx rotationMtx;
    Mtx_FromQuat(&rotationMtx, this->parent->transform->localRotation);

    // Extract vectors from rotation (swizzle XYZ for correct transformation (lol) )
    forward.x = -rotationMtx.r[2].x;
    forward.y = -rotationMtx.r[2].y;
    forward.z = -rotationMtx.r[2].z;

    right.x = rotationMtx.r[0].x;
    right.y = rotationMtx.r[0].y;
    right.z = rotationMtx.r[0].z;

    up.x = rotationMtx.r[1].x;
    up.y = rotationMtx.r[1].y;
    up.z = rotationMtx.r[1].z;

    // Calculate movement
    C3D_FVec movement {};
    movement = FVec3_Add(movement, FVec3_Scale(forward, (static_cast<float>(Input::circlePad.dy) / 128.0f) * moveSpeed * deltaTime));
    movement = FVec3_Add(movement, FVec3_Scale(right, (static_cast<float>(Input::circlePad.dx) / 128.0f) * moveSpeed * deltaTime));
    movement = FVec3_Add(movement, FVec3_Scale(up, ((Input::held & KEY_L ? -1 : (Input::held & KEY_R ? 1 : 0))) * moveSpeed * deltaTime));

    this->parent->transform->Translate(movement);
}