#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include <iostream>

#include "component.hpp"
#include "transform.hpp"

class GameObject
{
    public:
        GameObject();
        ~GameObject();

        void Update(float deltaTime);
        void Render();

        // stole from citro3d tutorial lol
		// https://github.com/tommai78101/homebrew
        template<typename Derived> std::shared_ptr<Derived> AddComponent(){
			static_assert(std::is_base_of<Component, Derived>::value, "Derived class is not subclass of Component.");
			std::shared_ptr<Derived> result(new Derived());
			result->SetParent(this);
			
			// Sort into vector based on update priority
			auto iter = std::upper_bound(this->components.begin(), this->components.end(), result);
			this->components.insert(iter, result);

			return result;
		}
		
		template<typename Derived, typename... TArgs> std::shared_ptr<Derived> AddComponent(TArgs&&... args){
			static_assert(std::is_base_of<Component, Derived>::value, "Derived class is not subclass of Component.");
			std::shared_ptr<Derived> result(new Derived(args...));
			result->SetParent(this);

			// Sort into vector based on update priority
			auto iter = std::upper_bound(this->components.begin(), this->components.end(), result);
			this->components.insert(iter, result);

			return result;
		}

        template<typename Derived> std::shared_ptr<Derived> GetComponent() {
			static_assert(std::is_base_of<Component, Derived>::value, "Derived class is not subclass of Component.");
			for (size_t i = 0; i < this->components.size(); i++){
				Derived* result = static_cast<Derived*>(this->components[i].get());
				if (result){
					return std::static_pointer_cast<Derived>(this->components[i]);
				}
			}
			return nullptr;
		}

		template<typename Derived> std::vector<std::shared_ptr<Derived>> GetComponents() {
			static_assert(std::is_base_of<Component, Derived>::value, "Derived class is not subclass of Component.");
			std::vector<std::shared_ptr<Derived>> result;
			for (size_t i = 0; i < this->components.size(); i++){
				Derived* component = static_cast<Derived*>(this->components[i].get());
				if (component){
					result.push_back(std::static_pointer_cast<Derived>(this->components[i]));
				}
			}
			return result;
		}

        std::shared_ptr<Transform> transform;
		int updatePriority = 0;
    private:
        std::vector<std::shared_ptr<Component>> components;
};