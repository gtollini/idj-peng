#include "../include/Face.h"
#include "../include/GameObject.h"

Face::Face(GameObject& associated):GameObject(associated){
	/* construir classe mãe*/
	hitpoints = 30;
}


void Face::Damage (int damage){
	hitpoints-=damage;
	if (hitpoints<0) associated.RequestDelete() /*Play Sound do associated? */ ;
}

void Face::Update(float dt){
}

void Face::Render(){
}

bool Is(std::string type){
	return type=="Face";
}
