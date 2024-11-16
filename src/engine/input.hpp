#pragma once

#include <3ds.h>

namespace Input
{
    extern u32 down, downRepeat, held, up;
    extern circlePosition circlePad, cStick;
    extern touchPosition touchScreen;

    void GatherInput();
};