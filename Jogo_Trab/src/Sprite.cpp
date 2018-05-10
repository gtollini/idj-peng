#include "SDL2/SDL_image.h"
#include "../include/State.h"
#include "../include/Sprite.h"
#include "../include/Game.h"
#include "../include/Resources.h"
#include "../include/Camera.h"

#include <iostream>


Sprite::Sprite(GameObject& associated): Component(associated){
	texture=nullptr;
	width=0;
	height=0;
	scale.x=1;
	scale.y=1;
}

Sprite::Sprite(std::string file, GameObject& associated): Component(associated){
	texture=nullptr;
	width=0;
	height=0;
	Open (file.c_str());
	scale.x=1;
	scale.y=1;
}

Sprite::Sprite(int x, int y,std::string file, GameObject& associated): Component(associated){
	texture=nullptr;
	width=0;
	height=0;
	Open (file.c_str());
	clipRect.x=x;
	clipRect.y=y;
	scale.x=1;
	scale.y=1;
}



Sprite::~Sprite(){
	resources.ClearImages();
}


void Sprite::Open(std::string file){
	this->texture=resources.GetImage(file);
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	SetClip (0,0,width, height);
	associated.box.w=(float)width;
	associated.box.h=(float)height;
}

void Sprite::SetClip(int x, int y, int w, int h){
	clipRect.x=x;
	clipRect.y=y;
	clipRect.w=w;
	clipRect.h=h;
}

void Sprite::Update(float dt){
}


void Sprite::Render(){
	SDL_Rect dstRect;
	dstRect.x= (int)(associated.box.x-Camera::GetInstance().pos.x);
	dstRect.y= (int)(associated.box.y-Camera::GetInstance().pos.y);
	dstRect.w= clipRect.w;
	dstRect.h= clipRect.h;

	SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, associated.angle, nullptr, SDL_FLIP_NONE);
}

void Sprite::Render(int srcX, int srcY, int h, int  w,  int dstX, int dstY){
	SDL_Rect srcrect = SDL_Rect{srcX, srcY, w, h};
	SDL_Rect dstrect = SDL_Rect{dstX,dstY,w*scale.x,h*scale.y};

	SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &srcrect, &dstrect);
}
void Sprite::SetScale(float ScaleX, float ScaleY){
	if (ScaleX!=0) 	scale.x=ScaleX;
	if (ScaleY!=0)	scale.y=ScaleY;

	this->Center();
}

Vec2 Sprite::GetScale(){
	return scale;
}

int Sprite::GetWidth(){
	return width*scale.x;
}

int Sprite::GetHeight(){
	return height*scale.y;
}

void Sprite::Center(){
	associated.box.x = associated.box.x - this->GetWidth()/2;
	associated.box.y = associated.box.y - this->GetWidth()/2;
}


bool Sprite::IsOpen(){
	return texture!=nullptr;
}

bool Sprite::Is(std::string type){
	return type=="Sprite";
}
