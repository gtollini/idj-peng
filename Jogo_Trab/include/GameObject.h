#ifndef GAMEOBJECT_CLASS
#define GAMEOBJECT_CLASS

#include <vector>
#include <iostream>
#include <memory>
#include "Rect.h"


/*Agora   que   você   implementou State usando   unique   pointers   para
manter um registro de GOs, você pode retornar à classe GameObject e
modificá-la   para,   ao   invés   de   usar   ponteiros   puros,   usar
unique_ptr<Component>
.   As   funções   que   você   terá   que   modificar   são
~GameObject
RemoveComponent
GetComponent
. Além da
declaração do vetor
components
.*/

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
