#include "../include/EndState.h"
#include "../include/GameData.h"
#include "../include/Music.h"
#include "../include/Sprite.h"
#include "../include/Text.h"
#include "../include/Resources.h"
#include "../include/InputManager.h"
#include "../include/TitleState.h"
#include "../include/Game.h"


std::string const winSpriteAdd = "assets/img/win.jpg";
std::string const winMusicAdd  = "assets/audio/endStateWin.ogg";

std::string const loseSpriteAdd = "assets/img/lose.jpg";
std::string const loseMusicAdd = "assets/audio/endStateLose.ogg";

const std::string fontAdd = "assets/font/Call me maybe.ttf";

#define MESSX	50
#define MESSY	450
const std::string message = "Press spacebar to play again, or ESC to exit";
#define SIZE 48


EndState::EndState(){
	GameObject *endObject = new GameObject();

	endObject->box.x=0;
	endObject->box.y=0;

	Sprite *screen = nullptr;

	if(GameData::playerVictory){
	   backgroundMusic = Music(winMusicAdd);
	   screen = new Sprite(*endObject, winSpriteAdd);
	    }
	else{
		backgroundMusic = Music(loseMusicAdd);
	    screen = new Sprite(*endObject, loseSpriteAdd);
	}

	endObject->AddComponent(screen);
	objectArray.emplace_back(endObject);

	backgroundMusic.Play(-1);

	GameObject *textObject = new GameObject();
	Text *text = new Text(*textObject, fontAdd, SIZE, Text::SOLID, message,(SDL_Color){255,0,0,0});
	textObject->AddComponent(text);

	textObject->box.SetPos(endObject->box.x+MESSX,endObject->box.y+MESSY);

	objectArray.emplace_back(textObject);
}

EndState::~EndState(){
	objectArray.clear();
}

void EndState::LoadAssets(){
	Resources::GetInstance().GetImage(winSpriteAdd);
	Resources::GetInstance().GetMusic(winMusicAdd);

	Resources::GetInstance().GetImage(loseSpriteAdd);
	Resources::GetInstance().GetMusic(loseMusicAdd);

	Resources::GetInstance().GetFont("fontAdd",SIZE );
}

void EndState::Update(float dt){
	quitRequested = InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY);


	if(InputManager::GetInstance().KeyPress(' ')){
			TitleState *title = new TitleState();
			popRequested = true;
			Game::GetInstance().Push(title);
	}
	UpdateArray(dt);

}

void EndState::Render(){
	RenderArray();
}

void EndState::Start(){
	LoadAssets();
	StartArray();
}

void EndState::Pause(){
	backgroundMusic.Stop(200);
}

void EndState::Resume(){

}
