#ifndef GAMEOBJECT_CLASS
#define GAMEOBJECT_CLASS

#include <vector>
#include <iostream>
#include "Rect.h"


/*Agora   que   você   implementou
State
  usando   unique   pointers   para
manter um registro de GOs, você pode retornar à classe
GameObject
  e
modificá-la   para,   ao   invés   de   usar   ponteiros   puros,   usar
unique_ptr<Component>
.   As   funções   que   você   terá   que   modificar   são
~GameObject
,
AddComponent
,
RemoveComponent
  e
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
		void RemoveComponent (Component * cpt);
		Component* GetComponent (std::string type);
		Rect box;

	private:
		std::vector <Component *> components;
		bool isDead;
};

#include "Component.h"

#endif
