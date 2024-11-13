#include <3ds.h>
#include <citro3d.h>
#include <citro2d.h>

#include "core.hpp"

int main()
{
    gfxInitDefault();
    gfxSet3D(true);
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);

    consoleInit(GFX_BOTTOM, NULL);

    {
        Core core;
        while (aptMainLoop())
        {
            hidScanInput();
            if (hidKeysDown() & KEY_START)
                break;
            
            core.Update();
            core.Render();
        }
    }

    C3D_Fini();
    gfxExit();

    exit(0);
}