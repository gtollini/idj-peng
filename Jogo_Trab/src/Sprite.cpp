#include "SDL2/SDL_image.h"
#include "../include/State.h"
#include "../include/Sprite.h"
#include "../include/Game.h"
#include <iostream>

#include "SDL_include.h"

Sprite::Sprite(GameObject& associated): Component(associated){
	texture=nullptr;
	width=0;
	height=0;
	clipRect=new SDL_Rect() ;
}
Sprite::Sprite(std::string file, GameObject& associated): Component(associated){
	texture=nullptr;
	width=0;
	height=0;
	clipRect=new SDL_Rect();
	Open (file.c_str());
}

Sprite::Sprite(int x, int y,std::string file, GameObject& associated): Component(associated){
	texture=nullptr;
	width=0;
	height=0;
	clipRect=new SDL_Rect();
	Open (file.c_str());
	clipRect->x=x;
	clipRect->y=y;
}



Sprite::~Sprite(){
	SDL_DestroyTexture(texture);
}


void Sprite::Open(std::string file){
	if (this->texture != nullptr) SDL_DestroyTexture(this->texture);
	this->texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(),file.c_str());
	if (this->texture==nullptr){
		printf ("Erro ao carregar textura em %s\n", file.c_str());
	}
	SDL_QueryTexture(texture, nullptr, nullptr, &height, &width);
	SetClip (0,0,height, width);
}

void Sprite::SetClip(int x, int y, int w, int h){
	clipRect->x=x;
	clipRect->y=y;
	clipRect->w=w;
	clipRect->h=h;
}

void Sprite::Update(float dt){

}


void Sprite::Render(){
	SDL_Rect srcrect = SDL_Rect{0,0,height,width};
	SDL_Rect dstrect = SDL_Rect{clipRect->x,clipRect->y,clipRect->h,clipRect->w};

	SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &srcrect, &dstrect);
}

int Sprite::GetWidth(){
	return width;
}

int Sprite::GetHeight(){
	return height;
}

bool Sprite::IsOpen(){
	return texture!=nullptr;
}

bool Sprite::Is(std::string type){
	return type=="Sprite";
}
