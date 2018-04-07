#include "../include/GameObject.h"
#include "../include/Component.h"
#include <iostream>


Component::Component (GameObject& associated) : associated(associated){
}

void Component::Update(float dt){

}
Component::~Component(){

}

void Component::Render(){

}


