#include "../include/State.h"

#include <memory>
#include <vector>

#include "../include/GameObject.h"

State::State() : started(false), popRequested(false), quitRequested(false){

}

State::~State(){
//	int size  = objectArray.size();
//	for (int i=0;i<size;i++){
//		objectArray[i]->RequestDelete();
//	}
	objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject (GameObject* go){
	std::shared_ptr<GameObject> go_sptr = std::shared_ptr<GameObject>(go);
	objectArray.emplace_back(go_sptr);

	if (started) go_sptr->Start();

	return std::weak_ptr<GameObject>(go_sptr);

}



std::weak_ptr<GameObject> State::GetObjectPtr(GameObject *go) {
    for(auto& it : objectArray){
        if(it.get() == go){
            return std::weak_ptr<GameObject>(it);
        }
}
    return std::weak_ptr<GameObject>();
}

/*
void State::Start(){

}

void State::Pause(){

};

void State::Resume(){

};
*/
/*
void State::Update(float dt){

};

void State::Render(){};
*/

bool State::PopRequested(){
	return popRequested;
}

bool State::QuitRequested(){
	return quitRequested;
}


void State::StartArray(){
	int size = objectArray.size();
	for (int i=0; i<size; i++){
		objectArray[i]->Start();
	}
}

void State::UpdateArray(float dt){
	int size = objectArray.size();
		for (int i=0; i<size; i++){
			objectArray[i]->Update(dt);
		}
}

void State::RenderArray() {
	int size = objectArray.size();
		for (int i=0; i<size; i++){
			objectArray[i]->Render();
		}
}
