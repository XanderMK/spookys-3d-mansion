#pragma once

#include <3ds.h>
#include <citro3d.h>
#include <citro2d.h>
#include "vshader_shbin.h"

#include "scene.hpp"
#include "mesh.hpp"


class Core
{
    public:
        Core();
        ~Core();

        void Update();
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
		C3D_Light light;
		C3D_LightLut lut_Phong;

		DVLB_s* vertexShader_dvlb;
		shaderProgram_s program;

        std::unique_ptr<C3D_RenderTarget> targetLeft;
        std::unique_ptr<C3D_RenderTarget> targetRight;

        float iod = 0.0f;

        Scene currentScene {{GameObject()}};
};

#define DISPLAY_TRANSFER_FLAGS \
	(GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | \
	GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | \
	GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))
#define CLEAR_COLOR 0x68B0D8FF
#define CLEAR_COLOR_2 0xFF0000FF

static const Vertex vertexList[] =
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
	{ 0.2f, 0.2f, 0.2f }, //ambient
	{ 0.4f, 0.4f, 0.4f }, //diffuse
	{ 0.8f, 0.8f, 0.8f }, //specular0
	{ 0.0f, 0.0f, 0.0f }, //specular1
	{ 0.0f, 0.0f, 0.0f }, //emission
};

static const int vertexListSize = (sizeof(vertexList) / sizeof(vertexList[0]));