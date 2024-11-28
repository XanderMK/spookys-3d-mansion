#pragma once

#include <3ds.h>
#include <citro3d.h>
#include <memory>

#include "component.hpp"
#include "gameobject.hpp"

class Follow : public Component
{
    public:
        Follow(GameObject *parent, std::shared_ptr<GameObject> objToFollow);
        ~Follow() = default;

        void Update(float deltaTime) override;
        void Render() override {}

        int updatePriority = 5;
    private:
        std::shared_ptr<GameObject> objToFollow;
};