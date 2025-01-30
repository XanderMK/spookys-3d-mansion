#pragma once

#include <vector>
#include <sstream>
#include <fstream>

#include "gameobject.hpp"

class Camera;
class FreeCam;
class Texture;
class Mesh;
class Player;
class AABBCollider;

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

        void AddScene(Scene scene, float weight);
        void LoadFromFile(std::string filename);
        void Clear();
        Scene GetRandomScene();
    private:
        std::vector<std::pair<Scene, float> > scenes;
        float totalWeight = 0.f;
};