#include <3ds.h>
#include <citro3d.h>
#include <citro2d.h>
#include <chrono>

#include "core.hpp"

int main()
{
    hidInit();
    gfxInitDefault();
    gfxSet3D(true);
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);

    consoleInit(GFX_BOTTOM, NULL);

    romfsInit();

    {
        Core core;
        while (aptMainLoop())
        {
            if (Input::down & KEY_START)
                break;

            static float deltaTime = 1.0f / 60.0f;
            auto start_time = std::chrono::high_resolution_clock::now();
            
            core.Update(deltaTime);
            core.Render();

            auto end_time = std::chrono::high_resolution_clock::now();

            // Convert from nanoseconds to seconds
            deltaTime = (end_time - start_time).count() / 1.0E9f;

            std::cout << deltaTime << std::endl;
        }
    } // boo!

    romfsExit();

    C3D_Fini();
    gfxExit();
    hidExit();
}