#pragma once

#include "3ds.h"
#include "citro3d.h"
#include <vector>
#include <memory>

#include "gameobject.hpp"

namespace Global
{
    extern int uLoc_projection;
    extern int uLoc_model;
    extern int uLoc_view;

    extern C3D_Mtx projectionMatrix;
    extern C3D_Mtx viewMatrix;
    extern C3D_LightEnv lightEnvironment;
    extern C3D_FogLut fog_Lut;
    extern C3D_Light light;
    extern C3D_LightLut lut_Phong;

    extern std::vector<std::shared_ptr<GameObject> > sceneObjects;

    extern bool loadNewScene;
};