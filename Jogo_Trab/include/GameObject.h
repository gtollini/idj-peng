#ifndef GAMEOBJECT_CLASS
#define GAMEOBJECT_CLASS

#include <vector>
#include <iostream>
#include <memory>
#include "Rect.h"

class Component;

class GameObject {
	public:
		GameObject();
		~GameObject();

		void Update (float dt);
		void Render();
		bool IsDead();
		void RequestDelete();
		void AddComponent (Component * cpt);
		void RemoveComponent (std::unique_ptr<Component> cpt);
		Component* GetComponent (std::string type);
		Rect box;

	private:
		std::vector <std::unique_ptr<Component>> components;
		bool isDead;
};

#include "Component.h"

#endif
