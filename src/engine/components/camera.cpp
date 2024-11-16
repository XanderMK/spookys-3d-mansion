#include "camera.hpp"

Camera::Camera(int uLoc_view) : uLoc_view(uLoc_view)
{
    Mtx_Identity(&cameraMatrix);
}

Camera::~Camera() = default;

void Camera::Update(float deltaTime)
{
    Mtx_Identity(&cameraMatrix);
    this->parent->transform->TransformMatrixInverse(&cameraMatrix);
    C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_view, &cameraMatrix);
}

C3D_Mtx Camera::GetCameraMatrix()
{
    return this->cameraMatrix;
}