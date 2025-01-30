#include "player.hpp"
#include "core.hpp"

Player::Player(GameObject *parent) : Component(parent)
{
    // Create new object for camera and set it as a child
    auto cam = std::make_shared<GameObject>();
    cam->transform->localPosition = defaultCameraPos;
    cam->AddComponent<Camera>(parent->scene->core->GetULoc_View());
    parent->children.push_back(cam);

    collider = parent->GetComponent<AABBCollider>();
    if (collider == nullptr)
        collider = parent->AddComponent<AABBCollider>(defaultColliderBounds);
}

void Player::Update(float deltaTime)
{
    // Rotation
    xRot -= (static_cast<float>(Input::cStick.dy) / 128.0f) * camSensitivity * deltaTime;
    yRot += (static_cast<float>(Input::cStick.dx) / 128.0f) * camSensitivity * deltaTime;

    // Clamp rotation on X-axis
    if (xRot < -90.0f)
        xRot = -90.0f;
    else if (xRot > 90.0f)
        xRot = 90.0f;
    
    // Reset angle on Y-axis to stay between 0-360
    if (yRot < 0.0f)
        yRot += 360.0f;
    else if (yRot > 360.0f)
        yRot -= 360.0f;

    this->parent->transform->SetRotation(FVec3_New(0, yRot, 0));
    this->parent->children[0]->transform->SetRotation(FVec3_New(xRot, 0, 0));


    // Movement

    C3D_FVec forward{}, right{};
    C3D_Mtx rotationMtx;
    Mtx_FromQuat(&rotationMtx, this->parent->transform->localRotation);

    // Extract vectors from rotation (swizzle XYZ for correct transformation)
    forward.x = -rotationMtx.r[2].x;
    forward.y = -rotationMtx.r[2].y;
    forward.z = -rotationMtx.r[2].z;

    right.x = rotationMtx.r[0].x;
    right.y = rotationMtx.r[0].y;
    right.z = rotationMtx.r[0].z;

    // Remove y vectors from movement and normalize (don't want to move up/down)
    forward.y = 0.0f;
    forward = FVec3_Normalize(forward);

    right.y = 0.0f;
    right = FVec3_Normalize(right);

    // Calculate movement
    C3D_FVec movement {};
    movement = FVec3_Add(movement, FVec3_Scale(forward, (static_cast<float>(Input::circlePad.dy) / 128.0f) * walkSpeed * deltaTime));
    movement = FVec3_Add(movement, FVec3_Scale(right, (static_cast<float>(Input::circlePad.dx) / 128.0f) * walkSpeed * deltaTime));

    // Move on each axis independently and check for collision
    parent->transform->Translate(FVec3_New(movement.x, 0.0f, 0.0f));
    if (collider->IsColliding())
        parent->transform->Translate(FVec3_New(-movement.x, 0.0f, 0.0f));

    parent->transform->Translate(FVec3_New(0.0f, 0.0f, movement.z));
    if (collider->IsColliding())
        parent->transform->Translate(FVec3_New(0.0f, 0.0f, -movement.z));
}