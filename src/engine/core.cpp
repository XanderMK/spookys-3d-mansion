#include "core.hpp"

Core::Core()
{
    // Set up render targets (so far only top screen with 3D)
    C3D_RenderTargetSetOutput(this->targetLeft,  GFX_TOP, GFX_LEFT,  DISPLAY_TRANSFER_FLAGS);
	C3D_RenderTargetSetOutput(this->targetRight, GFX_TOP, GFX_RIGHT, DISPLAY_TRANSFER_FLAGS);

    //Load vertex shader, then create a shader program to bind the vertex shader to.
    //The variables are automatically generated from PICA shader files when using "make" commands.
    this->vertexShader_dvlb = DVLB_ParseFile((u32*) vshader_shbin, vshader_shbin_size);
    shaderProgramInit(&this->program);
    shaderProgramSetVsh(&this->program, &this->vertexShader_dvlb->DVLE[0]);

    //Binding (like isaac).
    C3D_BindProgram(&this->program);

    //Get location of uniforms used in the vertex shader.
    this->uLoc_projection = shaderInstanceGetUniformLocation(this->program.vertexShader, "projection");
    this->uLoc_view = shaderInstanceGetUniformLocation(this->program.vertexShader, "view");
    this->uLoc_model = shaderInstanceGetUniformLocation(this->program.vertexShader, "model");

    //Initialize attributes, and then configure them for use with vertex shader.
    C3D_AttrInfo* attributeInfo = C3D_GetAttrInfo();
    AttrInfo_Init(attributeInfo);
    AttrInfo_AddLoader(attributeInfo, 0, GPU_FLOAT, 3); //First float array = vertex position.
    AttrInfo_AddLoader(attributeInfo, 1, GPU_FLOAT, 2); //Second float array = texture coordinates.
    AttrInfo_AddLoader(attributeInfo, 2, GPU_FLOAT, 3); //Third float array = normals.

    // Configure the first fragment shading substage to blend the fragment primary color
    // with the fragment secondary color.
    // See https://www.opengl.org/sdk/docs/man2/xhtml/glTexEnv.xml for more insight
    C3D_TexEnv* environment = C3D_GetTexEnv(0);
    C3D_TexEnvSrc(environment, C3D_Both, GPU_FRAGMENT_PRIMARY_COLOR, GPU_FRAGMENT_SECONDARY_COLOR);
    C3D_TexEnvOpAlpha(environment, GPU_TEVOP_A_SRC_ALPHA);
    C3D_TexEnvOpRgb(environment, GPU_TEVOP_RGB_SRC_COLOR);
    C3D_TexEnvFunc(environment, C3D_Both, GPU_ADD);

    //Lighting setup
    C3D_LightEnvInit(&this->lightEnvironment);
    C3D_LightEnvBind(&this->lightEnvironment);
    C3D_LightEnvMaterial(&this->lightEnvironment, &material);

    LightLut_Phong(&this->lut_Phong, 30);
    C3D_LightEnvLut(&this->lightEnvironment, GPU_LUT_D0, GPU_LUTINPUT_LN, false, &this->lut_Phong);

    C3D_FVec lightVector = { { 6.0, 0.5, 0.0, 0.0 } };

    C3D_LightInit(&this->light, &this->lightEnvironment);
    C3D_LightColor(&this->light, 1.0, 1.0, 1.0);
    C3D_LightPosition(&this->light, &lightVector);

    // Initialize matrices
    C3D_Mtx projection;
	Mtx_PerspStereoTilt(&projection, C3D_AngleFromDegrees(40.0f), C3D_AspectRatioTop, 0.3f, 100.0f, iod, 2.0f, false);

    C3D_Mtx identity;
    Mtx_Identity(&identity);

	// Update the uniforms
	C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_projection, &projection);
    C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_view, &identity);
	C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_model, &identity);

    // Create test objects
    std::shared_ptr<GameObject> cam = std::shared_ptr<GameObject>(new GameObject());
    cam->AddComponent<FreeCam>();
    cam->AddComponent<Camera>(uLoc_view);
    this->currentScene.gameObjects.push_back(cam);

    std::shared_ptr<GameObject> newObj = std::shared_ptr<GameObject>(new GameObject());
    newObj->transform->Translate(FVec3_New(0, 0, -5));
    newObj->AddComponent<Mesh>(static_cast<const void*>(cubeMesh), cubeMeshListSize);
    this->currentScene.gameObjects.push_back(newObj);
}

Core::~Core()
{
    shaderProgramFree(&this->program);
    DVLB_Free(this->vertexShader_dvlb);
}

void Core::Update(float deltaTime)
{
    Input::GatherInput();
    this->iod = osGet3DSliderState();

    for (auto & obj : this->currentScene.gameObjects)
    {
        obj->transform->Rotate(FVec3_New(0, C3D_AngleFromDegrees(30) * deltaTime, 0));

        obj->Update(deltaTime);
    }
}

void Core::Render()
{
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
    {
        C3D_RenderTargetClear(targetLeft, C3D_CLEAR_ALL, CLEAR_COLOR, 0);
        C3D_FrameDrawOn(targetLeft);

        // Update projection matrix
        C3D_Mtx projection;
        Mtx_PerspStereoTilt(&projection, C3D_AngleFromDegrees(40.0f), C3D_AspectRatioTop, 0.3f, 100.0f, -iod, 2.0f, false);

        for (auto & obj : this->currentScene.gameObjects)
        {
            // Update object matrix
            C3D_Mtx modelMtx;
            obj->transform->TransformMatrix(&modelMtx);
            C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_model, &modelMtx);

            obj->Render();
        }

        if (iod > 0.0f)
        {
            C3D_RenderTargetClear(targetRight, C3D_CLEAR_ALL, CLEAR_COLOR, 0);
            C3D_FrameDrawOn(targetRight);

            // Update projection matrix
            C3D_Mtx projection;
            Mtx_PerspStereoTilt(&projection, C3D_AngleFromDegrees(40.0f), C3D_AspectRatioTop, 0.3f, 100.0f, iod, 2.0f, false);

            for (auto & obj : this->currentScene.gameObjects)
            {
                // Update object matrix
                C3D_Mtx model;
                obj->transform->TransformMatrix(&model);
                C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_model, &model);

                obj->Render();
            }
        }
    }
    C3D_FrameEnd(0);
}