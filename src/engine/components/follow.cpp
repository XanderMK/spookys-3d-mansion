#include "follow.hpp"

Follow::Follow(GameObject *parent, std::shared_ptr<GameObject> objToFollow) : Component(parent), objToFollow(objToFollow)
{

}

void Follow::Update(float deltaTime)
{
    C3D_FVec dir = FVec3_Normalize(FVec3_Add(objToFollow->transform->localPosition, FVec3_Negate(this->parent->transform->localPosition)));

    this->parent->transform->Translate(FVec3_Scale(dir, deltaTime));
    this->parent->transform->localRotation = Quat_LookAt(this->parent->transform->localPosition, objToFollow->transform->localPosition, FVec3_New(0, 0, -1), FVec3_New(0, 1, 0));
}