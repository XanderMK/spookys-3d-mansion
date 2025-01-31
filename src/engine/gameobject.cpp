#include "gameobject.hpp"
#include "mesh.hpp"

GameObject::GameObject()
{
    this->transform = AddComponent<Transform>();
}

GameObject::GameObject(Scene *scene, GameObject *parent) : scene(scene), parent(parent)
{
    this->transform = AddComponent<Transform>();
}

GameObject::~GameObject() = default;

void GameObject::Update(float deltaTime)
{
    // Update components
    for (unsigned int i = 0; i < this->components.size(); i++)
    {
        this->components[i]->Update(deltaTime);
    }

    // Update children
    for (unsigned int i = 0; i < this->children.size(); i++)
    {
        this->children[i]->Update(deltaTime);
    }
}

void GameObject::Render()
{
    // Render all meshes
    std::vector<std::shared_ptr<Mesh> > meshes = this->GetComponents<Mesh>();
    for (const auto &mesh : meshes)
    {
        mesh->Render();
    }
}



void Transform::SetDirty()
{
    // Recursively set dirty so that all children also update
    this->dirty = true;

    for (auto & child : this->parent->children)
    {
        child->transform->SetDirty();
    }
}

void Transform::SetPosition(C3D_FVec position)
{
    this->localPosition.x = position.x;
    this->localPosition.y = position.y;
    this->localPosition.z = position.z;

    SetDirty();
}

void Transform::Translate(C3D_FVec translation)
{
    this->localPosition.x += translation.x;
    this->localPosition.y += translation.y;
    this->localPosition.z += translation.z;

    SetDirty();
}

void Transform::SetRotation(C3D_FVec rotation)
{
    this->localRotation = Quat_Identity();
    this->Rotate(rotation);

    SetDirty();
}

void Transform::Rotate(C3D_FVec rotation)
{
    this->localRotation = Quat_RotateZ(this->localRotation, C3D_AngleFromDegrees(rotation.z), true);
    this->localRotation = Quat_RotateY(this->localRotation, C3D_AngleFromDegrees(rotation.y), true);
    this->localRotation = Quat_RotateX(this->localRotation, C3D_AngleFromDegrees(rotation.x), true);

    SetDirty();
}

void Transform::SetScale(C3D_FVec scale)
{
    this->localScale.x = scale.x;
    this->localScale.y = scale.y;
    this->localScale.z = scale.z;

    SetDirty();
}

void Transform::ChangeScale(C3D_FVec scale)
{
    this->localScale.x += scale.x;
    this->localScale.y += scale.y;
    this->localScale.z += scale.z;

    SetDirty();
}

void Transform::UpdateCachedMatrices()
{
    /*
        Local Matrix
    */ 
    {
        // Init
        Mtx_Identity(&this->cachedLocalMtx);

        // Translate
        Mtx_Translate(&this->cachedLocalMtx, this->localPosition.x, this->localPosition.y, this->localPosition.z, true);

        // Rotate
        C3D_Mtx rotMtx;
        Mtx_FromQuat(&rotMtx, this->localRotation);
        Mtx_Multiply(&this->cachedLocalMtx, &this->cachedLocalMtx, &rotMtx);

        // Scale
        Mtx_Scale(&this->cachedLocalMtx, this->localScale.x, this->localScale.y, this->localScale.z);
    }

    /*
        Local Inverse Matrix
    */
    {
        // Init
        Mtx_Identity(&this->cachedLocalMtxInverse);

        // Scale
        Mtx_Scale(&this->cachedLocalMtxInverse, this->localScale.x, this->localScale.y, this->localScale.z);

        // Rotate
        C3D_Mtx rotMtx;
        Mtx_FromQuat(&rotMtx, this->localRotation);
        Mtx_Multiply(&this->cachedLocalMtxInverse, &this->cachedLocalMtxInverse, &rotMtx);

        // Translate
        Mtx_Translate(&this->cachedLocalMtxInverse, -this->localPosition.x, -this->localPosition.y, -this->localPosition.z, true);
    }
    

    /*
        Global Matrix
    */
    {
        // Init
        Mtx_Identity(&this->cachedGlobalMtx);

        // Initialize with parent's transform (or identity if no parent)
        if (this->parent->parent != nullptr)
        {
            auto globMtx = this->parent->parent->transform->TransformGlobalMatrix();
            Mtx_Multiply(&this->cachedGlobalMtx, &this->cachedGlobalMtx, &globMtx);
        }
        else
            Mtx_Identity(&this->cachedGlobalMtx);

        // Apply this object's transform
        Mtx_Multiply(&this->cachedGlobalMtx, &this->cachedGlobalMtx, &this->cachedLocalMtx);
    }
    

    /*
        Global Inverse Matrix
    */
    {
        // Init
        Mtx_Identity(&this->cachedGlobalMtxInverse);

        // Initialize with parent's transform (or identity if no parent)
        if (this->parent->parent != nullptr)
        {
            auto globMtxInv = this->parent->parent->transform->TransformGlobalMatrixInverse();
            Mtx_Multiply(&this->cachedGlobalMtx, &this->cachedGlobalMtx, &globMtxInv);
        }
        else
            Mtx_Identity(&this->cachedGlobalMtxInverse);

        // Apply this object's transform
        Mtx_Multiply(&this->cachedGlobalMtxInverse, &this->cachedGlobalMtxInverse, &this->cachedLocalMtxInverse);
    }

    // All matrices have been updated; remove flag
    this->dirty = false;
}

C3D_Mtx Transform::TransformLocalMatrix()
{
    if (this->dirty)
        UpdateCachedMatrices();

    return this->cachedLocalMtx;
}

C3D_Mtx Transform::TransformLocalMatrixInverse()
{
    if (this->dirty)
        UpdateCachedMatrices();

    return this->cachedLocalMtxInverse;
}

C3D_Mtx Transform::TransformGlobalMatrix()
{
    if (this->dirty)
        UpdateCachedMatrices();
    
    return this->cachedGlobalMtx;
}

C3D_Mtx Transform::TransformGlobalMatrixInverse()
{
    if (this->dirty)
        UpdateCachedMatrices();
    
    return this->cachedGlobalMtxInverse;
}