#include "../include/State.h"
#include "../include/Sprite.h"
#include "../include/Music.h"
#include "../include/Rect.h"
#include "../include/Face.h"
#include "../include/Vec2.h"
#include "../include/GameObject.h"
#include "../include/Sound.h"
#include "../include/TileMap.h"
#include "../include/TileSet.h"
#include "../include/InputManager.h"
#include "../include/CameraFollower.h"
#include "../include/Alien.h"
#include "../include/PenguinBody.h"
#include "../include/Collider.h"
#include "../include/Collision.h"

#include <cstdlib>
#include <ctime>
#include <memory>

#define PI 3.1415
#define TILEW 64
#define TILEH 64

#define UPDATE_MENU 0
#define RENDER_MENU 0

const std::string spriteAdd	= 	"assets/img/penguinface.png";
const std::string soundAdd 	= 	"assets/audio/boom.wav";
const std::string musicAdd 	= 	"assets/audio/stageState.ogg";
const std::string bgAdd 	= 	"assets/img/ocean.jpg";
const std::string tsAdd 	= 	"assets/img/tileset.png";
const std::string mapTxtAdd =	"assets/map/tileMap.txt";

State::State(){
	quitRequested = false;
	started = false;
	printf ("Inicializando Música...\n");
	music = new Music(musicAdd);
	printf ("	%s\n\n", music->IsOpen()?"ok":"erro");

	music->Play(1);
	printf ("Inicializando tileset...\n");
	TileSet *ts=nullptr;
	ts = new TileSet(TILEW, TILEH, tsAdd);
	printf ("	%s\n\n",ts!=nullptr?"ok":"erro");

	GameObject *bgObject = new GameObject();

	Sprite *bg = new Sprite(bgAdd, *bgObject);
	bg->SetClip(0,0,1024,600);
	CameraFollower* cf = new CameraFollower (*bgObject);

	bgObject->AddComponent(bg);
	bgObject->AddComponent(cf);
	objectArray.emplace_back(bgObject);

	GameObject *mapObject = new GameObject();
	objectArray.emplace_back(mapObject);

	printf ("Inicializando mapa...\n");
	TileMap *map = nullptr;
	map = new TileMap(*mapObject, mapTxtAdd, ts);
	printf ("	%s\n\n", map!=nullptr?"ok":"erro");
	mapObject->box.x=0;
	mapObject->box.y=0;
	mapObject->box.h=TILEH;
	mapObject->box.w=TILEW;
	objectArray.back()->AddComponent(map);

	GameObject *alienObject = new GameObject();
	alienObject->box.y= (300) ;
	alienObject->box.x= (512) ;

	Alien *alien = new Alien(*alienObject, 3);
	alienObject->AddComponent(alien);
	objectArray.emplace_back(alienObject);


	GameObject *pbodyObject = new GameObject();
	pbodyObject->box.SetPos(704, 640);

	PenguinBody *pbody = new PenguinBody(*pbodyObject);
	pbodyObject->AddComponent(pbody);
	objectArray.emplace_back(pbodyObject);

	Camera::GetInstance().Follow(pbodyObject);


}

State::~State(){
	objectArray.clear();
}

void State::LoadAssets(){
}


void State::Start(){
	LoadAssets();
	int size=objectArray.size();
	for (int i=0; i<size; i++){
		objectArray[i]->Start();
	}
	started=true;
}

void State::Update(float dt){
	//Input();

	int mouseX, mouseY;
	mouseX = InputManager::GetInstance().GetMouseX();
	mouseY = InputManager::GetInstance().GetMouseY();

	if (InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().IsKeyDown(ESCAPE_KEY)) {
		quitRequested = true;
	}

	Camera::GetInstance().Update(dt);


	int size = objectArray.size();
		GameObject *aux;
		for (int i=0; i<size; i++){
			if (UPDATE_MENU) printf ("	Initializing Update %d/%d...\n", i+1, size);
			objectArray[i]->Update(dt);
		}

		for (int j=0; j<size-1;j++){
			for (int k=j+1; k<size; k++){
				//printf ("aliv\n");
				Collider *a = nullptr,*b = nullptr;
				a=(Collider *) objectArray[j]->GetComponent("Collider");
				b=(Collider *) objectArray[k]->GetComponent("Collider");
				if (a != nullptr && b!=nullptr && Collision::IsColliding(a->box, b->box, objectArray[j]->angle, objectArray[k]->angle)){
					objectArray[j]->NotifyCollision(*objectArray[k]);
					objectArray[k]->NotifyCollision(*objectArray[j]);
				}
			}
		}

		for (int l=0; l<size; l++){
			if (objectArray[l]->IsDead()){
				objectArray.erase(objectArray.begin()+l);
				size--;
				l--;
			}
		}



	if (UPDATE_MENU) printf ("	All the updates are done!...\n");
}

void State::Render(){
	int size = objectArray.size();
		for (int i=0; i<size; i++){
			if (RENDER_MENU) printf ("	Initializing Render %d/%d...\n", i+1, size);
			objectArray[i]->Render();}
}

void State::AddObject(int mouseX, int mouseY){

	GameObject *newObject = new GameObject();
	Sprite *sprite = new Sprite(mouseX, mouseY, spriteAdd, *newObject);
	newObject->AddComponent(sprite);
	newObject->box.x=mouseX;
	newObject->box.y=mouseY;
	newObject->box.h=sprite->GetHeight();
	newObject->box.w=sprite->GetWidth();
	Sound *sound = new Sound(soundAdd, *newObject);
	Face *face = new Face(*newObject);
	newObject->AddComponent(face);
	newObject->AddComponent(sound);
	objectArray.emplace_back(newObject);

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


void State::Delete(){
	int l=objectArray.size();
	for (int i=0;i<l;i++){
		objectArray[i].reset();
	}
	delete this;
}


bool State::QuitRequested(){
	return quitRequested;
}

