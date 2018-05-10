#include "../include/CameraFollower.h"
#include "../include/Component.h"
#include "../include/GameObject.h"
#include "../include/Camera.h"

CameraFollower::CameraFollower(GameObject& associated) : Component (associated){

};

void CameraFollower::Update(float dt){
	associated.box.SetPos(Camera::GetInstance().pos);
}


void CameraFollower::Render(){

}




bool CameraFollower::Is(std::string type){
	return type=="CameraFollower";
}
