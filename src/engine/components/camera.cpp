#include "camera.hpp"

Camera::Camera(GameObject *parent) : Component(parent) {}

void Camera::Update(float deltaTime)
{
    auto mtx = this->parent->transform->TransformLocalMatrixInverse();
    C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, Global::uLoc_view, &mtx);
}