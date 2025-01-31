#pragma once

#include <3ds.h>
#include <citro3d.h>
#include <algorithm>
#include <memory>
#include <vector>
#include <iostream>

#include "component.hpp"

class Core;
struct Transform;
struct Scene;

class GameObject
{
    public:
        GameObject();
		GameObject(Scene *scene, GameObject *parent);
        ~GameObject();

        void Update(float deltaTime);
        void Render();

        // stole from citro3d tutorial lol
		// https://github.com/tommai78101/homebrew
        template<typename Derived> std::shared_ptr<Derived> AddComponent(){
			static_assert(std::is_base_of<Component, Derived>::value, "Derived class is not subclass of Component.");
			std::shared_ptr<Derived> result(new Derived(this));
			
			// Sort into vector based on update priority
			auto iter = std::upper_bound(this->components.begin(), this->components.end(), result);
			this->components.insert(iter, result);

			return result;
		}
		
		template<typename Derived, typename... TArgs> std::shared_ptr<Derived> AddComponent(TArgs&&... args){
			static_assert(std::is_base_of<Component, Derived>::value, "Derived class is not subclass of Component.");
			std::shared_ptr<Derived> result(new Derived(this, args...));

			// Sort into vector based on update priority
			auto iter = std::upper_bound(this->components.begin(), this->components.end(), result);
			this->components.insert(iter, result);

			return result;
		}

        template<typename Derived> std::shared_ptr<Derived> GetComponent() {
			static_assert(std::is_base_of<Component, Derived>::value, "Derived class is not subclass of Component.");
			for (size_t i = 0; i < this->components.size(); i++)
			{
				auto result = std::dynamic_pointer_cast<Derived>(this->components[i]);
				if (result != nullptr)
					return result;
			}
			return nullptr;
		}

		template<typename Derived> std::vector<std::shared_ptr<Derived>> GetComponents() {
			static_assert(std::is_base_of<Component, Derived>::value, "Derived class is not subclass of Component.");
			std::vector<std::shared_ptr<Derived>> result;
			for (size_t i = 0; i < this->components.size(); i++){
				auto component = std::dynamic_pointer_cast<Derived>(this->components[i]);
				if (component != nullptr){
					result.push_back(component);
				}
			}
			return result;
		}

		Scene *scene;
        std::shared_ptr<Transform> transform = nullptr;
		GameObject *parent = nullptr;
		std::vector<std::shared_ptr<GameObject>> children{};
		int updatePriority = 0;
    private:
        std::vector<std::shared_ptr<Component>> components{};
};

struct Transform : public Component
{
    Transform(GameObject *parent) : Component(parent), localPosition{0}, localRotation{Quat_Identity()}, localScale{1, 1, 1, 1} {}
    Transform(GameObject *parent, C3D_FVec position, C3D_FQuat rotation, C3D_FVec scale) : 
              Component(parent), localPosition(position), localRotation(rotation), localScale(scale) {}
    ~Transform() = default;

    void Update(float deltaTime) override {};
    void Render() override {};
    int updatePriority = -10;

    C3D_FVec localPosition;
    C3D_FQuat localRotation;
    C3D_FVec localScale;

	
	C3D_Mtx cachedLocalMtx, cachedGlobalMtx, cachedLocalMtxInverse, cachedGlobalMtxInverse;

	bool dirty = true;
	void SetDirty();

    void SetPosition(C3D_FVec position);
    void Translate(C3D_FVec translation);
    void SetRotation(C3D_FVec rotation);
    void Rotate(C3D_FVec rotation);
    void SetScale(C3D_FVec scale);
    void ChangeScale(C3D_FVec scale);

	void UpdateCachedMatrices();

    C3D_Mtx TransformLocalMatrix();
    C3D_Mtx TransformLocalMatrixInverse();

    C3D_Mtx TransformGlobalMatrix();
    C3D_Mtx TransformGlobalMatrixInverse();
};