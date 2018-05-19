#include "../include/TitleState.h"
#include "../include/GameObject.h"
#include "../include/Sprite.h"
#include "../include/Text.h"
#include "../include/InputManager.h"
#include "../include/Resources.h"
#include "../include/StageState.h"
#include "../include/Game.h"
#include "../include/CameraFollower.h"

const std::string spriteAdd = "assets/img/title.jpg";
const std::string fontAdd = "assets/font/Call me maybe.ttf";

#define MESSX	250
#define MESSY	450
const std::string message = "Press spacebar to start!";
#define SIZE 48

TitleState::TitleState(){
	GameObject *titleObject = new GameObject();

	titleObject->box.x=0;
	titleObject->box.y=0;

	CameraFollower *titleCF = new CameraFollower(*titleObject);

	Sprite * sprite = new Sprite(*titleObject, spriteAdd);
	titleObject->AddComponent(sprite);
	titleObject->AddComponent(titleCF);

	objectArray.emplace_back(titleObject);

	GameObject *textObject = new GameObject();
	Text *text = new Text(*textObject, fontAdd, SIZE, Text::SOLID, message,(SDL_Color){0,0,0,0});
	textObject->AddComponent(text);

	textObject->box.SetPos(titleObject->box.x+MESSX,titleObject->box.y+MESSY);

	objectArray.emplace_back(textObject);
}

TitleState::~TitleState(){
	objectArray.clear();
}

void TitleState::Update(float dt){
	quitRequested = InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY);


	if(InputManager::GetInstance().KeyPress(' ')){
			StageState *stage = new StageState();
			Game::GetInstance().Push(stage);
			popRequested=true;
	}


	UpdateArray(dt);
}

void TitleState::Render(){
	RenderArray();
}
void TitleState::Start() {
    LoadAssets();
    StartArray();
}

void TitleState::Pause() {

}

void TitleState::Resume() {
}

void TitleState::LoadAssets(){
	Resources::GetInstance().GetFont(fontAdd, SIZE);
	Resources::GetInstance().GetImage(spriteAdd);
}
