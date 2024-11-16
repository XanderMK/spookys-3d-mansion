#include "input.hpp"
#include <stdlib.h>

u32 Input::down{}, Input::downRepeat{}, Input::held{}, Input::up{};
circlePosition Input::circlePad{}, Input::cStick{};
touchPosition Input::touchScreen{};

void Input::GatherInput()
{
    hidScanInput();

    down =          hidKeysDown();
    downRepeat =    hidKeysDownRepeat();
    held =          hidKeysHeld();
    up =            hidKeysUp();

    static constexpr int circlePadDeadzone = 0.1f * 128;
    static constexpr int cStickDeadzone = 0.05f * 128;

    hidCircleRead(&circlePad);
    if (abs(circlePad.dx) < circlePadDeadzone) circlePad.dx = 0;
    if (abs(circlePad.dy) < circlePadDeadzone) circlePad.dy = 0;

    hidCstickRead(&cStick);
    if (abs(cStick.dx) < cStickDeadzone) cStick.dx = 0;
    if (abs(cStick.dy) < cStickDeadzone) cStick.dy = 0;

    hidTouchRead(&touchScreen);
}