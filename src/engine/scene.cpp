#include "scene.hpp"
#include "core.hpp"

void Scene::LoadFromString(std::string in)
{
    // Reset all context
    Collider::sceneColliders.clear();
    Global::sceneObjects.clear();
    gameObjects.clear();
    Resources::ClearResources();

    std::stringstream s(in);

    std::string object;
    while (std::getline(s, object, '\n'))
    {
        auto newObj = std::make_shared<GameObject>();

        std::stringstream objS(object);
        std::string component;
        while (std::getline(objS, component, '|'))
        {
            std::stringstream compS(component);
            std::vector<std::string> parameters;
            std::string parameter;
            while (std::getline(compS, parameter, ','))
            {
                parameters.push_back(parameter);
            }

            // Load object based on type and parameters
            if (parameters[0] == "transform")
            {
                C3D_FVec pos, rot, scale;

                pos.x = std::stof(parameters[1]);
                pos.y = std::stof(parameters[2]);
                pos.z = std::stof(parameters[3]);

                rot.x = std::stof(parameters[4]);
                rot.y = std::stof(parameters[5]);
                rot.z = std::stof(parameters[6]);

                scale.x = std::stof(parameters[7]);
                scale.y = std::stof(parameters[8]);
                scale.z = std::stof(parameters[9]);

                newObj->transform->SetPosition(pos);
                newObj->transform->SetRotation(rot);
                newObj->transform->SetScale(scale);
            }
            else if (parameters[0] == "mesh")
            {
                newObj->AddComponent<Mesh>(parameters[1]);
            }
            else if (parameters[0] == "camera")
            {
                newObj->AddComponent<Camera>();
            }
            else if (parameters[0] == "freecam")
            {
                newObj->AddComponent<FreeCam>();
            }
            else if (parameters[0] == "texture")
            {
                newObj->AddComponent<Texture>(Resources::GetTexture(parameters[1]));
            }
            else if (parameters[0] == "player")
            {
                newObj->AddComponent<Player>(stof(parameters[1]), stof(parameters[2]));
            }
            else if (parameters[0] == "door")
            {
                newObj->AddComponent<Door>();
            }
            else if (parameters[0] == "aabbcollider")
            {
                auto col = newObj->AddComponent<AABBCollider>(FVec3_New(std::stof(parameters[1]), std::stof(parameters[2]), std::stof(parameters[3])));
                Collider::sceneColliders.push_back(col);
            }
            else
            {
                //std::cout << "parameter " << parameters[0] << " is INVALID!" << std::endl;
            }
        }

        gameObjects.push_back(newObj);
    }

    Global::sceneObjects = gameObjects;
}

void Scene::LoadFromFile(std::string filename)
{
    std::ifstream ifstream;
    ifstream.open(filename);

    std::stringstream s;
    s << ifstream.rdbuf();

    // now we have text, so just use the above method
    LoadFromString(s.str());
}


void SceneCollection::AddScene(std::string scene, float weight)
{
    if (weight <= 0.f)
    {
        std::cout << "Tried to add scene with weight of zero or less!" << std::endl;
        return;
    }

    scenes.push_back(std::pair(scene, weight));
    totalWeight += weight;
}

void SceneCollection::LoadFromFile(std::string filename)
{
    std::ifstream ifstream;
    ifstream.open(filename);

    std::stringstream s;
    s << ifstream.rdbuf();

    std::string line;
    while (std::getline(s, line, '\n'))
    {
        std::vector<std::string> parts;
        std::string part;
        std::stringstream part_s(line);
        while (std::getline(part_s, part, ':'))
        {
            parts.push_back(part);
        }

        AddScene("romfs:/Scenes/" + parts[0], std::stof(parts[1]));
    }
}

void SceneCollection::Clear()
{
    scenes.clear();
}

// Adapted from https://stackoverflow.com/questions/1761626/weighted-random-numbers#1761646 
std::string SceneCollection::GetRandomScene()
{
    float random = ((float)rand() / (float)RAND_MAX);
    float finalWeight = random * totalWeight;

    for (size_t i = 0; i < scenes.size(); i++)
    {
        if (finalWeight < scenes[i].second)
            return scenes[i].first;
        finalWeight -= scenes[i].second;
    }

    std::cout << "finding a scene failed" << std::endl;

    // Shouldn't get here, return first element just in case
    return scenes[0].first;
}