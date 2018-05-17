#ifndef COMPONENT_CLASS
#define COMPONENT_CLASS

#include "SDL2/SDL.h"
#include <iostream>
#include "GameObject.h"


class Component{
	public:
		virtual void Start();
		Component (GameObject& associated);
		virtual ~Component();
		virtual void Update (float dt);
		virtual void Render() = 0;
		virtual bool Is(std::string type)=0;

		virtual void NotifyCollision(GameObject& other);
	protected:
		GameObject& associated;
};





#endif
