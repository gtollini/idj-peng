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
#include <cstdlib>
#include <ctime>
#include <memory>

#define PI 3.1415
#define TILEW 64
#define TILEH 64

const std::string spriteAdd	= 	"assets/img/penguinface.png";
const std::string soundAdd 	= 	"assets/audio/boom.wav";
const std::string musicAdd 	= 	"assets/audio/stageState.ogg";
const std::string bgAdd 	= 	"assets/img/tileset.png";
const std::string mapTxtAdd =	"assets/map/tileMap.txt";

State::State(){
	quitRequested = false;
	printf ("Inicializando Música...\n");
	music = new Music(musicAdd);
	printf ("	%s\n\n", music->IsOpen()?"ok":"erro");

	/*GameObject *bgObject = new GameObject();
	objectArray.emplace_back(bgObject);
	Sprite *bg = new Sprite(bgAdd, *bgObject);
	bg->SetClip(0,0,600,1024);
	objectArray.back()->AddComponent(bg);*/

	music->Play(1);
	printf ("Inicializando tileset...\n");
	TileSet *ts=nullptr;
	ts = new TileSet(TILEW, TILEH, bgAdd);
	printf ("	%s\n\n",ts!=nullptr?"ok":"erro");


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
}

State::~State(){
	objectArray.clear();
}

void State::LoadAssets(){
}


void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
			quitRequested = true;
		}

		// Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.

				if(go->box.Contains((float)mouseX ,(float)mouseY)) {
					Face* face = (Face*)go->GetComponent( "Face" );
					if ( nullptr != face ) {
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					}
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0)+Vec2( mouseX, mouseY );

				AddObject((int)objPos.x, (int)objPos.y);
			}
		}
	}
}


void State::Update(float dt){
	Input();
	int size = objectArray.size();
		for (int i=0; i<size; i++){
			objectArray[i]->Update(dt);}
}

void State::Render(){
	int size = objectArray.size();
		for (int i=0; i<size; i++){
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
	sound->Play(1);
	newObject->AddComponent(sound);
	objectArray.emplace_back(newObject);

}
bool State::QuitRequested(){
	return quitRequested;
}

