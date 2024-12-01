#pragma once

#include <3ds.h>
#include <citro3d.h>
#include <citro2d.h>
#include <iostream>
#include "vshader_shbin.h"
#include "FoodDemon_t3x.h"

#include "input.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "freecam.hpp"
#include "mesh.hpp"
#include "testmeshswapper.hpp"
#include "follow.hpp"

class Core
{
    public:
        Core();
        ~Core();

        void Update(float deltaTime);
        void Render();

        float GetIOD() { return this->iod; };
        Scene GetCurrentScene() { return this->currentScene; }
    private:
        int uLoc_projection;
		int uLoc_model;
		int uLoc_view;

		C3D_Mtx projectionMatrix;
		C3D_Mtx viewMatrix;
		C3D_LightEnv lightEnvironment;
		C3D_FogLut fog_Lut;
		C3D_Light light;
		C3D_LightLut lut_Phong;

		C3D_Tex FoodDemon_tex;

		DVLB_s* vertexShader_dvlb;
		shaderProgram_s program;

        C3D_RenderTarget* targetLeft = C3D_RenderTargetCreate(240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
		C3D_RenderTarget* targetRight = C3D_RenderTargetCreate(240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);

        float iod;

        Scene currentScene {};
};

#define DISPLAY_TRANSFER_FLAGS \
	(GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | \
	GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | \
	GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))
#define CLEAR_COLOR 0x000000FF

// Helper function for loading a texture from memory
static bool loadTextureFromMem(C3D_Tex* tex, C3D_TexCube* cube, const void* data, size_t size)
{
	Tex3DS_Texture t3x = Tex3DS_TextureImport(data, size, tex, cube, false);
	if (!t3x)
		return false;

	// Delete the t3x object since we don't need it
	Tex3DS_TextureFree(t3x);
	return true;
}


static constexpr Vertex cubeMesh[] =
{
	// First face (PZ)
	// First triangle
	{ { -0.5f, -0.5f, +0.5f },{ 0.0f, 0.0f },{ 0.0f, 0.0f, +1.0f } },
	{ { +0.5f, -0.5f, +0.5f },{ 1.0f, 0.0f },{ 0.0f, 0.0f, +1.0f } },
	{ { +0.5f, +0.5f, +0.5f },{ 1.0f, 1.0f },{ 0.0f, 0.0f, +1.0f } },
	// Second triangle
	{ { +0.5f, +0.5f, +0.5f },{ 1.0f, 1.0f },{ 0.0f, 0.0f, +1.0f } },
	{ { -0.5f, +0.5f, +0.5f },{ 0.0f, 1.0f },{ 0.0f, 0.0f, +1.0f } },
	{ { -0.5f, -0.5f, +0.5f },{ 0.0f, 0.0f },{ 0.0f, 0.0f, +1.0f } },

	// Second face (MZ)
	// First triangle
	{ { -0.5f, -0.5f, -0.5f },{ 0.0f, 0.0f },{ 0.0f, 0.0f, -1.0f } },
	{ { -0.5f, +0.5f, -0.5f },{ 1.0f, 0.0f },{ 0.0f, 0.0f, -1.0f } },
	{ { +0.5f, +0.5f, -0.5f },{ 1.0f, 1.0f },{ 0.0f, 0.0f, -1.0f } },
	// Second triangle
	{ { +0.5f, +0.5f, -0.5f },{ 1.0f, 1.0f },{ 0.0f, 0.0f, -1.0f } },
	{ { +0.5f, -0.5f, -0.5f },{ 0.0f, 1.0f },{ 0.0f, 0.0f, -1.0f } },
	{ { -0.5f, -0.5f, -0.5f },{ 0.0f, 0.0f },{ 0.0f, 0.0f, -1.0f } },

	// Third face (PX)
	// First triangle
	{ { +0.5f, -0.5f, -0.5f },{ 0.0f, 0.0f },{ +1.0f, 0.0f, 0.0f } },
	{ { +0.5f, +0.5f, -0.5f },{ 1.0f, 0.0f },{ +1.0f, 0.0f, 0.0f } },
	{ { +0.5f, +0.5f, +0.5f },{ 1.0f, 1.0f },{ +1.0f, 0.0f, 0.0f } },
	// Second triangle
	{ { +0.5f, +0.5f, +0.5f },{ 1.0f, 1.0f },{ +1.0f, 0.0f, 0.0f } },
	{ { +0.5f, -0.5f, +0.5f },{ 0.0f, 1.0f },{ +1.0f, 0.0f, 0.0f } },
	{ { +0.5f, -0.5f, -0.5f },{ 0.0f, 0.0f },{ +1.0f, 0.0f, 0.0f } },

	// Fourth face (MX)
	// First triangle
	{ { -0.5f, -0.5f, -0.5f },{ 0.0f, 0.0f },{ -1.0f, 0.0f, 0.0f } },
	{ { -0.5f, -0.5f, +0.5f },{ 1.0f, 0.0f },{ -1.0f, 0.0f, 0.0f } },
	{ { -0.5f, +0.5f, +0.5f },{ 1.0f, 1.0f },{ -1.0f, 0.0f, 0.0f } },
	// Second triangle
	{ { -0.5f, +0.5f, +0.5f },{ 1.0f, 1.0f },{ -1.0f, 0.0f, 0.0f } },
	{ { -0.5f, +0.5f, -0.5f },{ 0.0f, 1.0f },{ -1.0f, 0.0f, 0.0f } },
	{ { -0.5f, -0.5f, -0.5f },{ 0.0f, 0.0f },{ -1.0f, 0.0f, 0.0f } },

	// Fifth face (PY)
	// First triangle
	{ { -0.5f, +0.5f, -0.5f },{ 0.0f, 0.0f },{ 0.0f, +1.0f, 0.0f } },
	{ { -0.5f, +0.5f, +0.5f },{ 1.0f, 0.0f },{ 0.0f, +1.0f, 0.0f } },
	{ { +0.5f, +0.5f, +0.5f },{ 1.0f, 1.0f },{ 0.0f, +1.0f, 0.0f } },
	// Second triangle
	{ { +0.5f, +0.5f, +0.5f },{ 1.0f, 1.0f },{ 0.0f, +1.0f, 0.0f } },
	{ { +0.5f, +0.5f, -0.5f },{ 0.0f, 1.0f },{ 0.0f, +1.0f, 0.0f } },
	{ { -0.5f, +0.5f, -0.5f },{ 0.0f, 0.0f },{ 0.0f, +1.0f, 0.0f } },

	// Sixth face (MY)
	// First triangle
	{ { -0.5f, -0.5f, -0.5f },{ 0.0f, 0.0f },{ 0.0f, -1.0f, 0.0f } },
	{ { +0.5f, -0.5f, -0.5f },{ 1.0f, 0.0f },{ 0.0f, -1.0f, 0.0f } },
	{ { +0.5f, -0.5f, +0.5f },{ 1.0f, 1.0f },{ 0.0f, -1.0f, 0.0f } },
	// Second triangle
	{ { +0.5f, -0.5f, +0.5f },{ 1.0f, 1.0f },{ 0.0f, -1.0f, 0.0f } },
	{ { -0.5f, -0.5f, +0.5f },{ 0.0f, 1.0f },{ 0.0f, -1.0f, 0.0f } },
	{ { -0.5f, -0.5f, -0.5f },{ 0.0f, 0.0f },{ 0.0f, -1.0f, 0.0f } },
};

static const C3D_Material material =
{
	{ 1.0f, 1.0f, 1.0f }, //ambient
	{ 0.1f, 0.1f, 0.1f }, //diffuse
	{ 0.3f, 0.3f, 0.3f }, //specular0
	{ 0.0f, 0.0f, 0.0f }, //specular1
	{ 0.0f, 0.0f, 0.0f }, //emission
};

static constexpr int cubeMeshListSize = (sizeof(cubeMesh) / sizeof(cubeMesh[0]));


static constexpr Vertex vertexList[] =
{
	// First face (PZ)
	// First triangle
	{ { -0.5f, -0.5f, +0.5f },{ 0.0f, 0.0f },{ 0.0f, 0.0f, +1.0f } },
	{ { +0.5f, -0.5f, +0.5f },{ 1.0f, 0.0f },{ 0.0f, 0.0f, +1.0f } },
	{ { +0.5f, +0.5f, +0.5f },{ 1.0f, 1.0f },{ 0.0f, 0.0f, +1.0f } },
};

static constexpr int vertexListSize = (sizeof(vertexList) / sizeof(vertexList[0]));