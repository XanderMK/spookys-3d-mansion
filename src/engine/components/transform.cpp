#include "transform.hpp"
#include <iostream>

Transform::~Transform() = default;

void Transform::SetPosition(C3D_FVec position)
{
    this->position.x = position.x;
    this->position.y = position.y;
    this->position.z = position.z;
}

void Transform::Translate(C3D_FVec translation)
{
    this->position.x += translation.x;
    this->position.y += translation.y;
    this->position.z += translation.z;
}

void Transform::SetRotation(C3D_FVec rotation)
{
    this->rotation = Quat_Identity();
    this->Rotate(rotation);
}

void Transform::Rotate(C3D_FVec rotation)
{
    this->rotation = Quat_RotateZ(this->rotation, rotation.z, true);
    this->rotation = Quat_RotateY(this->rotation, rotation.y, true);
    this->rotation = Quat_RotateX(this->rotation, rotation.x, true);
}

void Transform::SetScale(C3D_FVec scale)
{
    this->scale.x = scale.x;
    this->scale.y = scale.y;
    this->scale.z = scale.z;
}

void Transform::ChangeScale(C3D_FVec scale)
{
    this->scale.x += scale.x;
    this->scale.y += scale.y;
    this->scale.z += scale.z;
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

void Transform::TransformMatrixInverse(C3D_Mtx* mtx)
{
    // Initialize
    Mtx_Identity(mtx);

    // Scale
    Mtx_Scale(mtx, this->scale.x, this->scale.y, this->scale.z);

    // Rotate
    C3D_Mtx rotMtx;
    Mtx_FromQuat(&rotMtx, this->rotation);
    Mtx_Multiply(mtx, mtx, &rotMtx);

    // Translate
    Mtx_Translate(mtx, -this->position.x, -this->position.y, -this->position.z, true);
}