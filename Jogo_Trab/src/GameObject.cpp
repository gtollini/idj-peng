#include "../include/GameObject.h"
#include "../include/TileMap.h"
#include "../include/CameraFollower.h"
#include "../include/Camera.h"

#define UPDATE_MENU 0
#define RENDER_MENU 0

GameObject::GameObject(){
	isDead = false;
	started=false;
	angle=0;
}


GameObject::~GameObject(){
	int size = components.size();
	for (int i=size-1; i>0; i--){
		components[i].reset();
	}
	components.clear();
}

void GameObject::Update(float dt){
	int size = components.size();
	if (UPDATE_MENU) printf ("Initializing Update...\n");
		for (int i=0; i<size; i++){
			components[i]->Update(dt);
			if (UPDATE_MENU) printf ("Done Updating:%s - %d/%d\n", components[i]->Is("Minion")?"Minion":(components[i]->Is("Alien")?"Alien":(components[i]->Is("TileMap")?"TileMap":(components[i]->Is("Sprite")?"Sprite":(components[i]->Is("CameraFollower")?"CameraFollower":"Irrelevant")))), i+1, size);
		}
		if (UPDATE_MENU) printf ("Done Updating!\n");

}

void GameObject::Render(){
	int size = components.size();

		for (int i=0; i<size; i++){
			components[i]->Render();
			if (RENDER_MENU) printf ("Done Rendering:%s - %d/%d\n", components[i]->Is("Minion")?"Minion":(components[i]->Is("Alien")?"Alien":(components[i]->Is("TileMap")?"TileMap":(components[i]->Is("Sprite")?"Sprite":"Irrelavant"))), i+1, size);
		}
		if (RENDER_MENU) printf ("Done Rendering!\n");
}



bool GameObject::IsDead(){
	return isDead;
}

void GameObject::RequestDelete(){
	isDead=true;
}

void GameObject::AddComponent(Component* cpt){
	components.emplace_back(cpt);
}

void GameObject::RemoveComponent(std::unique_ptr<Component> cpt){
	int size = components.size();
		for (int i=0; i<size; i++){
			if (components[i]==cpt){
				components[i].release();
			}
		}
}

Component * GameObject::GetComponent(std::string type){
	int size = components.size();
			for (int i=0; i<size; i++){
				if (components[i]->Is(type)){
					return components[i].get();
				}
			}
	return nullptr;
}

void GameObject::Start(){
	started=true;
	int size = components.size();
	for (int i=0; i<size; i++){
		components[i]->Start();
	}
}

void GameObject::NotifyCollision(GameObject& other){
	int size = components.size();
		for (int i=0; i<size; i++){
			components[i]->NotifyCollision(other);
		}
}
