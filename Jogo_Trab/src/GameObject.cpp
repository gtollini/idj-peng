#include "../include/GameObject.h"

GameObject::GameObject(){
	isDead = false;
}

GameObject::~GameObject(){
	components.clear();
}

void GameObject::Update(float dt){
	int size = components.size;
		for (int i=0; i<size; i++){
			components[i]->Update(dt);
		}
}

void GameObject::Render(){
	int size = components.size;
		for (int i=0; i<size; i++){
			components[i]->Render();
		}

}

bool GameObject::IsDead(){
	return isDead;
}

void GameObject::RequestDelete(){
	isDead=true;
}

void GameObject::AddComponent(Component* cpt){
	components.push_back(cpt);
}

void GameObject::RemoveComponent(Component * cpt){
	int size = components.size;
		for (int i=0; i<size; i++){
			if (components[i]==cpt){
				delete components[i];
			}
		}
}

Component * GameObject::GetComponent(std::string type){
	int size = components.size;
			for (int i=0; i<size; i++){
				if (components[i]->Is(type)){
					return components[i];
				}
			}
	return nullptr;
}



