#include "../include/Face.h"
#include "../include/GameObject.h"
#include "../include/InputManager.h"
#include "../include/Sound.h"
Face::Face(GameObject& associated): Component(associated){
	hitpoints = 30;
}


void Face::Damage (int damage){
	hitpoints-=damage;
	if (hitpoints<=0){
		Sound *compSound = (Sound *) associated.GetComponent("Sound");
		if (compSound!=nullptr) compSound->Play(1);
		associated.RequestDelete();
	}
}

void Face::Update(float dt){
	if (InputManager::GetInstance().IsMouseDown(SDL_BUTTON_LEFT) && associated.box.Contains(InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY())) Damage(rand());
}

void Face::Render(){
}

bool Face::Is(std::string type){
	return type=="Face";
}
