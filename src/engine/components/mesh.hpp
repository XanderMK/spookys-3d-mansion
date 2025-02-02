#pragma once

#include <3ds.h>
#include <citro3d.h>
#include "ufbx.h"
#include <array>
#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include "global.hpp"
#include "gameobject.hpp"
#include "component.hpp"
#include "texture.hpp"
#include "resources.hpp"
#include "model.hpp"

class Mesh : public Component
{
    public:
        Mesh(GameObject *parent) : Component(parent) {};
        Mesh(GameObject *parent, std::string &filename);
        ~Mesh();

        void Update(float deltaTime) override;
        void Render() override;

    private:
        std::string filename;
        std::shared_ptr<Model> model;
};