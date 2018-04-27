#include "../include/GameObject.h"
#include "../include/TileMap.h"
#include "../include/CameraFollower.h"
GameObject::GameObject(){
	isDead = false;
}

GameObject::~GameObject(){
	int size = components.size();
	for (int i=0; i<size; i++){
		components[i].release();
	}
	components.clear();
}

void GameObject::Update(float dt, float cameraX, float cameraY){
	int size = components.size();
		for (int i=0; i<size; i++){
			if (components[i]->Is("CameraFollower")){
				CameraFollower *cf;
				cf = (CameraFollower *) components[i].get();
				cf->Update(dt, cameraX, cameraY);
				//printf ("x:%f 	y:%f\n", this->box.x, this->box.y);
			}
			else
				components[i]->Update(dt);
		}

}

void GameObject::Render(int cameraX, int cameraY){
	int size = components.size();

		for (int i=0; i<size; i++){
			if (components[i]->Is("TileMap")){
				TileMap *aux;
				aux = (TileMap *)components[i].get();
				aux->Render(cameraX, cameraY);
			}
			else{
				components[i]->Render();
			}
		}
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



