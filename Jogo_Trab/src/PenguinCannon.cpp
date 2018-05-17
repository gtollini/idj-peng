#include "../include/PenguinCannon.h"
#include "../include/Component.h"
#include "../include/Bullet.h"
#include "../include/InputManager.h"
#include "../include/Game.h"
#include "../include/Sprite.h"
#include "../include/GameObject.h"
#include "../include/Collider.h"

#include <cmath>
#define PI 3.1415

#define COOLDOWN 1000
#define BULLET_SPEED 0.5
#define BULLET_DAMAGE 100
#define BULLET_MAXDISTANCE 1000

const std::string bulletSpriteAdd	= 	"assets/img/penguinbullet.png";
const std::string bodySpriteAdd		= 	"assets/img/cubngun.png";


PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : Component(associated), pbody(penguinBody){
	angle=0;

	Sprite *bulletSprite = new Sprite(associated, bodySpriteAdd);
	associated.AddComponent(bulletSprite);

	Collider *collider = new Collider(associated);
	associated.AddComponent(collider);

	associated.angle = 0;
	time.Restart();

}


void PenguinCannon::Start(){

}

void PenguinCannon::Render(){

}

void PenguinCannon::Update(float dt){
	if (pbody.lock()==nullptr){
		delete this;
	}
	time.Update(dt);
	associated.box.x = pbody.lock()->box.x - (associated.box.w/2 - pbody.lock()->box.w/2);
	associated.box.y = pbody.lock()->box.y - (associated.box.h/2 - pbody.lock()->box.h/2);

	angle = atan2(InputManager::GetInstance().GetMouseY() + Camera::GetInstance().pos.y - associated.box.GetCenter().y, InputManager::GetInstance().GetMouseX() +Camera::GetInstance().pos.x - associated.box.GetCenter().x);
	associated.angle=angle*180/PI;

	if (InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT)){
		Shoot();
	}
}

bool PenguinCannon::Is(std::string type){
	return type=="PenguinCannon";
}

void PenguinCannon::Shoot(){
	if (time.Get() > COOLDOWN){
		time.Restart();
		GameObject *bulletObject = new GameObject();
		bulletObject->box=associated.box;

		bulletObject->box.x = associated.box.x + associated.box.w/4;
		bulletObject->box.y = associated.box.y + associated.box.h/4;


		Bullet *bullet = new Bullet(*bulletObject, angle, BULLET_SPEED, BULLET_DAMAGE, BULLET_MAXDISTANCE, bulletSpriteAdd,4,100, false);
		bulletObject->AddComponent(bullet);
		Game::GetInstance().GetState().AddObject(bulletObject);}

}

void PenguinCannon::NotifyCollision(GameObject& other){
/*	Bullet *bullet =(Bullet *) other.GetComponent("Bullet");
	if (bullet  != nullptr){
		hp-=bullet->GetDamage();
		printf ("%d\n", hp);
	}*/
}

