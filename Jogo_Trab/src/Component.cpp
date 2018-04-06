#include "../include/GameObject.h"
#include "../include/Component.h"
#include <iostream>


Component::Component (GameObject& associated) : associated{associated}{
	this->associated = associated;
	associated.AddComponent(this);
}

void Component::Update(float dt){

}


void Component::Render(){

}


