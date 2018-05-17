#include "../include/Collider.h"
#include "../include/GameObject.h"
#include "../include/Vec2.h"

//#define DEBUG

#ifdef DEBUG
#include "../include/Camera.h"
#include "../include/Game.h"
#define PI 3.1415

#include <SDL2/SDL.h>
#endif // DEBUG

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated), scale(scale), offset(offset){

}



void Collider::Update(float dt){
	box.w=associated.box.w*scale.x;
	box.h=associated.box.h*scale.y;

	box.x=associated.box.x + associated.box.w/2 - box.w/2;
	box.y=associated.box.y + associated.box.h/2 - box.h/2;




}

void Collider::Render() {
#ifdef DEBUG
	Vec2 center( box.GetCenter() );
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y) - center).GetRotated( associated.angle/(180/PI) )
					+ center - Camera::GetInstance().pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};

	point = (Vec2(box.x + box.w, box.y) - center).GetRotated( associated.angle/(180/PI) )
					+ center - Camera::GetInstance().pos;
	points[1] = {(int)point.x, (int)point.y};

	point = (Vec2(box.x + box.w, box.y + box.h) - center).GetRotated( associated.angle/(180/PI) )
					+ center - Camera::GetInstance().pos;
	points[2] = {(int)point.x, (int)point.y};

	point = (Vec2(box.x, box.y + box.h) - center).GetRotated( associated.angle/(180/PI) )
					+ center - Camera::GetInstance().pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}


bool Collider::Is(std::string type){
	return type=="Collider";
}

void Collider::SetScale(Vec2 scale){
	this->scale = scale;
}

void Collider::SetOffset(Vec2 offset){
	this->offset=offset;
}
