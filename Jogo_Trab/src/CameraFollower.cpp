#include "../include/CameraFollower.h"
#include "../include/Component.h"
#include "../include/GameObject.h"
#include "../include/Camera.h"

CameraFollower::CameraFollower(GameObject& associated) : Component (associated){

};

void CameraFollower::Update(float dt){

}

void CameraFollower::Update(float dt, float x,float y){
	associated.box.x= x;
	associated.box.y= y;
}

void CameraFollower::Render(){

}




bool CameraFollower::Is(std::string type){
	return type=="CameraFollower";
}
