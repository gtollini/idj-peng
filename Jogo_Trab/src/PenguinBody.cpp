#include "../include/PenguinBody.h"
#include "../include/GameObject.h"
#include "../include/Component.h"
#include "../include/Sprite.h"
#include "../include/PenguinCannon.h"
#include "../include/Game.h"
#include "../include/InputManager.h"
#include "../include/Collider.h"
#include "../include/Bullet.h"
#include "../include/Sound.h"
#include "../include/GameData.h"


#define PI 3.1415

#define A 0.05
#define SPEED_MAX 0.5
#define W PI/32

PenguinBody* PenguinBody::player = nullptr;

const std::string bodySpriteAddress  =  "assets/img/penguin.png";
const std::string deathSpriteAddress =  "assets/img/penguindeath.png";
const std::string explosionSoundAddress =  "assets/audio/boom.wav";

PenguinBody::PenguinBody(GameObject& associated) : Component(associated){
	linearSpeed = 0;
	angle = 0;
	hp=100;

	Sprite *bodySprite = new Sprite(associated, bodySpriteAddress);
	associated.AddComponent(bodySprite);
	associated.angle = 0;
	player=this;

	Collider *collider = new Collider(associated);
	associated.AddComponent(collider);
}

void PenguinBody::Start(){
	GameObject *cannonObject = new GameObject();
	PenguinCannon *cannon = new PenguinCannon(*cannonObject, Game::GetInstance().GetCurrentState().GetObjectPtr(&associated));
	cannonObject->AddComponent(cannon);
	pcannon=Game::GetInstance().GetCurrentState().AddObject(cannonObject);

}



PenguinBody::~PenguinBody(){
	player=nullptr;
}

void PenguinBody::Render(){

}

void PenguinBody::Update(float dt){
	if (InputManager::GetInstance().IsKeyDown('w')){
		if (linearSpeed < SPEED_MAX)linearSpeed+=A;
	}
	else{
		if (linearSpeed > 0) linearSpeed-=A;
	}
	if (InputManager::GetInstance().IsKeyDown('s')){
		if (linearSpeed > -SPEED_MAX/2)linearSpeed-=A;
	}
	else{
		if (linearSpeed < 0) linearSpeed+=A;
	}

	if (InputManager::GetInstance().IsKeyDown('a')){
		angle-=W;
	}
	if (InputManager::GetInstance().IsKeyDown('d')){
		angle+=W;
	}

	speed.x=linearSpeed;
	speed.y=0;

	speed=speed.GetRotated(angle);

	associated.angle=angle*180/PI;
	associated.box.x+= speed.x*dt;
	associated.box.y+= speed.y*dt;

}

bool PenguinBody::Is(std::string type){
	return type=="PenguinBody";
}
void PenguinBody::NotifyCollision(GameObject& other){
	Bullet *bullet =(Bullet *) other.GetComponent("Bullet");
	if (bullet  != nullptr && bullet->targetsPlayer){
		hp-=bullet->GetDamage();
		printf ("Penguin: %d\n", hp);

		if (hp<=0){
			Camera::GetInstance().Unfollow();

			associated.RequestDelete();
			pcannon.lock()->RequestDelete();

			GameObject *explosionObject = new GameObject();
			Sprite * explosionSprite = new Sprite(*explosionObject , deathSpriteAddress, 5, 100, 0.5);
			explosionObject->AddComponent(explosionSprite);

			Sound *explosionSound = new Sound(explosionSoundAddress, *explosionObject);
			explosionObject->AddComponent(explosionSound);
			explosionSound->Play();

			explosionObject->box.x = associated.box.GetCenter().x - explosionObject->box.w/2 ;//+ Camera::GetInstance().pos.x;
			explosionObject->box.y = associated.box.GetCenter().y - explosionObject->box.h/2 ;//+ Camera::GetInstance().pos.y;


			Game::GetInstance().GetCurrentState().AddObject(explosionObject);

			GameData::playerVictory = false;

		}
	}
}

Vec2 PenguinBody::GetCenter(){
	return associated.box.GetCenter();
}
