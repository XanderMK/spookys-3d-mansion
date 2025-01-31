#pragma once

#include <vector>
#include <sstream>
#include <fstream>

#include "gameobject.hpp"
#include "camera.hpp"
#include "freecam.hpp"
#include "texture.hpp"
#include "mesh.hpp"
#include "player.hpp"
#include "door.hpp"
#include "collider.hpp"

struct Scene
{
    std::vector<std::shared_ptr<GameObject> > gameObjects;
    Core *core;

    void LoadFromString(std::string in);
    void LoadFromFile(std::string filename);
};

struct SceneCollection
{
    public:
        SceneCollection() = default;
        ~SceneCollection() = default;

        void AddScene(std::string scene, float weight);
        void LoadFromFile(std::string filename);
        void Clear();
        std::string GetRandomScene();
    private:
        std::vector<std::pair<std::string, float> > scenes;
        float totalWeight = 0.f;
};