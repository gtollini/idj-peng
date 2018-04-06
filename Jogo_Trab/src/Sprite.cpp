#include "SDL2/SDL_image.h"
#include "../include/State.h"
#include "../include/Sprite.h"
#include "../include/Game.h"


Sprite::Sprite(){
	texture=nullptr;
	width=0;
	height=0;
	clipRect=nullptr;
}
Sprite::Sprite(char * file){
	Sprite();
	Open (file);
}

Sprite::~Sprite(){
	SDL_DestroyTexture(texture);
}


void Sprite::Open(char * file){
	if (texture != nullptr) SDL_DestroyTexture(texture);
	texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(),file);
	if (texture==nullptr){
		printf ("Erro ao carregar textura em %s\n", file);
	}
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	SetClip (0,0,width, height);
}

void Sprite::SetClip(int x, int y, int w, int h){
	clipRect->x=x;
	clipRect->y=y;
	clipRect->w=w;
	clipRect->h=h;
}
void Sprite::Render (int x, int y){
	SDL_Rect * dstrect;
	dstrect->x=x;
	dstrect->y=y;
	dstrect->h=height;
	dstrect->w=width;

	SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, clipRect, dstrect);
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

