#include "camera.hpp"

Camera::Camera(GameObject *parent, int uLoc_view) : Component(parent), uLoc_view(uLoc_view) {}

void Camera::Update(float deltaTime)
{
    auto mtx = this->parent->transform->TransformGlobalMatrixInverse();
    C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_view, &mtx);
}