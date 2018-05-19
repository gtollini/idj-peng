/**/


#include "../include/StageState.h"

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
#include "../include/GameData.h"
#include "../include/EndState.h"
#include "../include/Game.h"
#include "../include/TitleState.h"

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

const std::string alienSpriteAdd	= 	"assets/img/alien.png";
const std::string deathSpriteAddress =  "assets/img/aliendeath.png";
const std::string explosionSoundAddress =  "assets/audio/boom.wav";

const std::string minionSpriteAdd	= 	"assets/img/minion.png";
const std::string bulletSpriteAdd	= 	"assets/img/minionbullet2.png";

#define NALIENS 3

StageState::StageState(){
	quitRequested = false;
	started = false;
	printf ("Inicializando Música...\n");
	backgroundMusic = new Music(musicAdd);
	printf ("	%s\n\n", backgroundMusic->IsOpen()?"ok":"erro");


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


	for (int i=0; i<NALIENS; i++){
		GameObject *alienObject = new GameObject();
		alienObject->box.y= (std::rand() % 1408) ;
		alienObject->box.x= (std::rand() % 1280) ;

		Alien *alien = new Alien(*alienObject, 3);
		alienObject->AddComponent(alien);
		objectArray.emplace_back(alienObject);}


	GameObject *pbodyObject = new GameObject();
	pbodyObject->box.SetPos(704, 640);

	PenguinBody *pbody = new PenguinBody(*pbodyObject);
	pbodyObject->AddComponent(pbody);
	objectArray.emplace_back(pbodyObject);

	tileSet=ts;
	Camera::GetInstance().Follow(pbodyObject);

	backgroundMusic->Play(1);
	printf ("OK\n");
}

StageState::~StageState(){
	objectArray.clear();
}

void StageState::LoadAssets(){
	Resources::GetInstance().GetSound(soundAdd);
	Resources::GetInstance().GetMusic(musicAdd);
	Resources::GetInstance().GetImage(bgAdd);
	Resources::GetInstance().GetImage(tsAdd);

	Resources::GetInstance().GetImage(alienSpriteAdd);
	Resources::GetInstance().GetImage(deathSpriteAddress);
	Resources::GetInstance().GetSound(explosionSoundAddress);

	Resources::GetInstance().GetImage(minionSpriteAdd);
	Resources::GetInstance().GetImage(bulletSpriteAdd);
}

void StageState::Update(float dt){
	//Input();

	int mouseX, mouseY;
	mouseX = InputManager::GetInstance().GetMouseX();
	mouseY = InputManager::GetInstance().GetMouseY();

	quitRequested = InputManager::GetInstance().QuitRequested();
	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		TitleState *title = new TitleState();
		popRequested = true;
		Game::GetInstance().Push(title);
	}

	Camera::GetInstance().Update(dt);

	int size = objectArray.size();
	UpdateArray(dt);

	for (int j=0; j<size-1;j++){
		for (int k=j+1; k<size; k++){
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

	 if(!PenguinBody::player){
	     popRequested = true;
	     EndState *defeat = new EndState();
	     Game::GetInstance().Push(defeat);
	}
	 if (Alien::alienCount ==0){
		 GameData::playerVictory=true;
		 popRequested = true;
		 EndState *victory = new EndState();
		Game::GetInstance().Push(victory);
	 }



	if (UPDATE_MENU) printf ("	All the updates are done!...\n");
}

void StageState::Render(){
	RenderArray();
}

void StageState::Start(){
    LoadAssets();
    StartArray();
    started=true;
}


void StageState::Pause() {
	backgroundMusic->Stop(200);
}

void StageState::Resume() {

}


