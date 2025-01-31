#include "global.hpp"

int Global::uLoc_projection{};
int Global::uLoc_model{};
int Global::uLoc_view{};

C3D_Mtx Global::projectionMatrix{};
C3D_Mtx Global::viewMatrix{};
C3D_LightEnv Global::lightEnvironment{};
C3D_FogLut Global::fog_Lut{};
C3D_Light Global::light{};
C3D_LightLut Global::lut_Phong{};

std::vector<std::shared_ptr<GameObject> > Global::sceneObjects{};

bool Global::loadNewScene = false;