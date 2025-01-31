#include "collider.hpp"

std::vector<std::shared_ptr<Collider> > Collider::sceneColliders{};

bool AABBCollider::IsColliding()
{
    for (auto &collider : sceneColliders)
    {
        if (IsColliding(collider))
            return true;
    }
    return false;
}

bool AABBCollider::IsColliding(std::shared_ptr<Collider> other)
{
    if (other.get() == this) return false;

    auto aabb = std::dynamic_pointer_cast<AABBCollider>(other);
    if (aabb != nullptr)
    {
        C3D_FVec pos = this->parent->transform->localPosition;
        C3D_FVec otherPos = aabb->parent->transform->localPosition;
        
        return (
            (pos.x - (bounds.x / 2.0f) <= otherPos.x + (aabb->bounds.x / 2.0f)) &&
            (pos.x + (bounds.x / 2.0f) >= otherPos.x - (aabb->bounds.x / 2.0f)) &&
            (pos.y - (bounds.y / 2.0f) <= otherPos.y + (aabb->bounds.y / 2.0f)) &&
            (pos.y + (bounds.y / 2.0f) >= otherPos.y - (aabb->bounds.y / 2.0f)) &&
            (pos.z - (bounds.z / 2.0f) <= otherPos.z + (aabb->bounds.z / 2.0f)) &&
            (pos.z + (bounds.z / 2.0f) >= otherPos.z - (aabb->bounds.z / 2.0f))
        );
    }
    return false;
}