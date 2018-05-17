#include "../include/Bullet.h"
#include "../include/Sprite.h"
#include "../include/Collider.h"
#include "../include/Alien.h"
#include "../include/PenguinBody.h"

#define PI 3.1415

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount, float frameTime, bool targetsPlayer): Component(associated){
	Sprite *bulletSprite = new Sprite(associated, sprite, frameCount, frameTime);
	associated.AddComponent(bulletSprite);
	this->speed.x=speed;
	this->speed.y=0;
	this->speed=this->speed.GetRotated(angle);
	distanceLeft=maxDistance;
	this->damage=damage;

	associated.angle=angle*180/PI;

	Collider *collider = new Collider(associated);
	associated.AddComponent(collider);

	this->targetsPlayer = targetsPlayer;
}

void Bullet::Update(float dt){
	Vec2 ds;
	ds.x = speed.x*dt;
	ds.y = speed.y*dt;

	associated.box.x+=ds.x;
	associated.box.y+=ds.y;

	distanceLeft = distanceLeft - ds.Abs();
	if (distanceLeft<=0) associated.RequestDelete();
}

void Bullet::Render(){

}

bool Bullet::Is(std::string type){
	return type=="Bullet";
}

int Bullet::GetDamage(){
	return damage;
}

void Bullet::NotifyCollision(GameObject& other){
	Bullet *bullet =(Bullet *) other.GetComponent("Bullet");
	if (bullet  != nullptr){
		//?
	}
	else{
		PenguinBody * pb = (PenguinBody*) other.GetComponent("PenguinBody");
		if (pb!=nullptr && targetsPlayer){
			associated.RequestDelete();
		}
		else{
			Alien * alien = (Alien *) other.GetComponent("Alien");
			if (alien !=nullptr && !targetsPlayer){
			associated.RequestDelete();
			}
		}
	}
}

