#pragma once

#include "component.hpp"

#include <citro3d.h>

struct Transform : public Component
{
    Transform() : position{}, rotation{}, scale{} {}
    Transform(C3D_FVec position, C3D_FQuat rotation, C3D_FVec scale) : 
              position(position), rotation(rotation), scale(scale) {}
    ~Transform();

    void Update() override {};
    void Render() override {};
    int updatePriority = -10;

    C3D_FVec position;
    C3D_FQuat rotation;
    C3D_FVec scale;

    void Translate(C3D_FVec translation);
    void Rotate(C3D_FVec rotation);
    void ChangeScale(C3D_FVec scale);
};