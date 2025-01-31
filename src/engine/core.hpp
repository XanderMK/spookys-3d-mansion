#pragma once

#include <3ds.h>
#include <citro3d.h>
#include <citro2d.h>
#include <iostream>
#include "vshader_shbin.h"

#include "global.hpp"
#include "input.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "freecam.hpp"
#include "mesh.hpp"
#include "collider.hpp"

class Core
{
    public:
        Core();
        ~Core();

        void Update(float deltaTime);
        void Render();

        float GetIOD() { return this->iod; };
        Scene GetCurrentScene() { return this->scene; }
		std::vector<std::shared_ptr<GameObject>> GetAllObjectsInScene() { return this->scene.gameObjects; }
    private:
		DVLB_s* vertexShader_dvlb;
		shaderProgram_s program;

        C3D_RenderTarget* targetLeft = C3D_RenderTargetCreate(240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
		C3D_RenderTarget* targetRight = C3D_RenderTargetCreate(240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);

        float iod;

		SceneCollection sceneCollection{};
        Scene scene{};
};

constexpr u32 DISPLAY_TRANSFER_FLAGS = \
	(GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | \
	GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | \
	GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO));
constexpr u32 CLEAR_COLOR = 0x000000FF;