#pragma once

class GameObject;

struct Component
{
    Component() = default;
    virtual ~Component() = default;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;

    virtual void SetParent(GameObject* parent) { this->parent = parent; }

    GameObject *parent;
    int updatePriority = 0;

    virtual bool operator <(const Component &other)
    {
        return this->updatePriority < other.updatePriority;
    }
};