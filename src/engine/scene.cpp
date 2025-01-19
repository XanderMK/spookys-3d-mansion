#include "scene.hpp"
#include "core.hpp"

void Scene::LoadFromString(std::string in)
{
    gameObjects.clear();
    
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
                newObj->AddComponent<Mesh>(parameters[1], core->GetLightEnvironment());
            }
            else if (parameters[0] == "camera")
            {
                newObj->AddComponent<Camera>(core->GetULoc_View());
            }
            else if (parameters[0] == "freecam")
            {
                newObj->AddComponent<FreeCam>();
            }
        }

        gameObjects.push_back(newObj);
    }
}

void Scene::LoadFromFile(std::string filename)
{
    gameObjects.clear();

    std::ifstream ifstream;
    ifstream.open(filename);

    std::stringstream s;
    s << ifstream.rdbuf();

    ifstream.close();

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
                newObj->AddComponent<Mesh>(parameters[1], core->GetLightEnvironment());
            }
            else if (parameters[0] == "camera")
            {
                newObj->AddComponent<Camera>(core->GetULoc_View());
            }
            else if (parameters[0] == "freecam")
            {
                newObj->AddComponent<FreeCam>();
            }
        }

        gameObjects.push_back(newObj);
    }
}