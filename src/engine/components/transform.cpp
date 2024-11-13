#include "transform.hpp"
#include <iostream>

Transform::~Transform() = default;

void Transform::Translate(C3D_FVec translation)
{
    // Swizzle translation vector so it matches expected XYZW orientation
    this->position.x += translation.w;
    this->position.y += translation.z;
    this->position.z += translation.y;
}

void Transform::Rotate(C3D_FVec rotation)
{
    // Swizzle rotation vector so it matches expected XYZW orientation
    this->rotation = Quat_RotateZ(this->rotation, rotation.y, true);
    this->rotation = Quat_RotateX(this->rotation, rotation.w, true);
    this->rotation = Quat_RotateY(this->rotation, rotation.z, true);
}

void Transform::SetScale(C3D_FVec scale)
{
    // Swizzle scaling vector so it matches expected XYZW orientation
    this->scale.x = scale.w;
    this->scale.y = scale.z;
    this->scale.z = scale.y;
}

void Transform::ChangeScale(C3D_FVec scale)
{
    // Swizzle scaling vector so it matches expected XYZW orientation
    this->scale.x += scale.w;
    this->scale.y += scale.z;
    this->scale.z += scale.y;
}

void Transform::TransformMatrix(C3D_Mtx* mtx)
{
    // Initialize
    Mtx_Identity(mtx);

    // Translate
    Mtx_Translate(mtx, this->position.x, this->position.y, this->position.z, true);

    // Rotate
    C3D_Mtx rotMtx;
    Mtx_FromQuat(&rotMtx, this->rotation);
    Mtx_Multiply(mtx, mtx, &rotMtx);

    // Scale
    Mtx_Scale(mtx, this->scale.x, this->scale.y, this->scale.z);
}