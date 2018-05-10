#include "../include/Minion.h"
#include "../include/Sprite.h"
#include "../include/GameObject.h"
#include "../include/Component.h"
#include "../include/Vec2.h"
#include "../include/InputManager.h"
#include "../include/Bullet.h"
#include "../include/Game.h"

#include <cmath>
#include <iostream>


#define R 150
const float W = PI/2;

#define BULLET_SPEED 1
#define BULLET_DAMAGE 10
#define BULLET_MAXDISTANCE 1000

const std::string minionSpriteAdd	= 	"assets/img/minion.png";
const std::string bulletSpriteAdd	= 	"assets/img/minionbullet1.png";

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : Component (associated), alienCenter(alienCenter){

	this->arc=arcOffsetDeg;
	Sprite *sprite = new Sprite(0,0,minionSpriteAdd, associated);
	associated.AddComponent(sprite);

	Vec2 initPos;
	initPos.x=R;
	initPos.y=0;
	initPos=initPos.GetRotated(this->arc);


	associated.box.w = sprite->GetWidth();
	associated.box.h = sprite->GetHeight();

	associated.box.Center();
}


void Minion::Update (float dt){

	arc+=W*dt/1000;

	associated.angle=-180*arc/PI;


	while (arc>=2*PI) arc-=2*PI;
	Vec2 pos = Vec2(0, R, arc);
	Rect alienPos = alienCenter.lock()->box;
	alienPos.x = alienPos.x + alienCenter.lock()->box.h/4;
	alienPos.y = alienPos.y + alienCenter.lock()->box.w/4;
	associated.box.SetPos(pos+alienPos.Pos());
}

void Minion::Render (){

}

bool Minion::Is(std::string type){
	return type=="Minion";
}

Vec2 Minion::Pos(){
	return associated.box.Pos();
}

void Minion::Shoot (Vec2 target){
	GameObject *bulletObject = new GameObject();
	bulletObject->box=associated.box;

	bulletObject->box.x = associated.box.x + associated.box.w/4;
	bulletObject->box.y = associated.box.y + associated.box.h/4;

	target.x -= associated.box.w/4;
	target.y -= associated.box.h/4;

	Bullet *bullet = new Bullet(*bulletObject, std::atan2(target.y, target.x), BULLET_SPEED, BULLET_DAMAGE, BULLET_MAXDISTANCE, bulletSpriteAdd);
	bulletObject->AddComponent(bullet);
	Game::GetInstance().GetState().AddObject(bulletObject);
}
