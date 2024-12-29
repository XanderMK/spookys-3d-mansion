#pragma once

#include <3ds.h>
#include <citro3d.h>
#include <citro2d.h>
#include <iostream>
#include "vshader_shbin.h"

#include "input.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "freecam.hpp"
#include "mesh.hpp"
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

static const C3D_Material material =
{
	{ 0.1f, 0.1f, 0.1f }, //ambient
	{ 1.0f, 1.0f, 1.0f }, //diffuse
	{ 0.0f, 0.0f, 0.0f }, //specular0
	{ 0.0f, 0.0f, 0.0f }, //specular1
	{ 0.0f, 0.0f, 0.0f }, //emission
};