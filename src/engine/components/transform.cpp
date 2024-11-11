#include "transform.hpp"

Transform::~Transform() = default;

void Transform::Translate(C3D_FVec translation)
{
    this->position.x += translation.x;
    this->position.y += translation.y;
    this->position.z += translation.z;
}

void Transform::Rotate(C3D_FVec rotation)
{
    Quat_RotateZ(this->rotation, rotation.z, true);
    Quat_RotateX(this->rotation, rotation.x, true);
    Quat_RotateY(this->rotation, rotation.y, true);
}

void Transform::ChangeScale(C3D_FVec scale)
{
    this->scale.x += scale.x;
    this->scale.y += scale.y;
    this->scale.z += scale.z;
}