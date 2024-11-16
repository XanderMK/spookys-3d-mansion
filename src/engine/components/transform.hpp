#pragma once

#include "component.hpp"

#include <citro3d.h>

struct Transform : public Component
{
    Transform() : position{0}, rotation{Quat_Identity()}, scale{1, 1, 1, 1} {}
    Transform(C3D_FVec position, C3D_FQuat rotation, C3D_FVec scale) : 
              position(position), rotation(rotation), scale(scale) {}
    ~Transform();

    void Update(float deltaTime) override {};
    void Render() override {};
    int updatePriority = -10;

    C3D_FVec position;
    C3D_FQuat rotation;
    C3D_FVec scale;

    void SetPosition(C3D_FVec position);
    void Translate(C3D_FVec translation);
    void SetRotation(C3D_FVec rotation);
    void Rotate(C3D_FVec rotation);
    void SetScale(C3D_FVec scale);
    void ChangeScale(C3D_FVec scale);

    void TransformMatrix(C3D_Mtx *mtx);
    void TransformMatrixInverse(C3D_Mtx* mtx);
};