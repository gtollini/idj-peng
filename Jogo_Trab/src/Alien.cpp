#include "../include/Alien.h"
#include "../include/Sprite.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"
#include "../include/Minion.h"
#include "../include/Game.h"
#include "../include/Collider.h"
#include "../include/Bullet.h"
#include "../include/Sound.h"
#include "../include/PenguinBody.h"

#define W 0.001
#define COOLDOWN 1000
const float V = 0.5; // Constante proporcional à velocidade base do Alien

const std::string alienSpriteAdd	= 	"assets/img/alien.png";
const std::string deathSpriteAddress =  "assets/img/aliendeath.png";
const std::string explosionSoundAddress =  "assets/audio/boom.wav";

int Alien::alienCount = 0;

Alien::Alien(GameObject& associated, int nMinions) : Component(associated){
	Sprite *sprite = new Sprite(0, 0, alienSpriteAdd, associated);
	associated.AddComponent(sprite);

	associated.box.h=(float)sprite->GetHeight();
	associated.box.w=(float)sprite->GetWidth();
	associated.box.Center();
	this->nMinions=nMinions;
	hp=100;
	speed.x=0;
	speed.y=0;


	Collider *collider = new Collider(associated);
	associated.AddComponent(collider);

	alienCount++;
	state=RESTING;


}


void Alien::Start(){
	state=RESTING;
	for (int i=0; i<nMinions; i++){
			GameObject *minionObject = new GameObject();
			Minion *minion = new Minion(*minionObject, Game::GetInstance().GetCurrentState().GetObjectPtr(&associated), (float)(i*2*PI/(nMinions)));
			minionObject->AddComponent(minion);
			minionArray.push_back(Game::GetInstance().GetCurrentState().AddObject(minionObject));
		}
}

void Alien::Update(float dt){
	associated.angle += 180*W*dt/PI;

	if (state==RESTING){
		restTimer.Update(dt);
		if (restTimer.Get() > COOLDOWN){
			state=MOVING;
			destination = PenguinBody::player->GetCenter();
			destination.x -= associated.box.w/2;
			destination.y -= associated.box.h/2;
			speed = (Vec2){V, 0}.GetRotated(atan2(destination.y - associated.box.y,destination.x - associated.box.x));

		}
	}

	if (state==MOVING){
		if ( (destination - associated.box.Pos()).Abs()<= V*dt){
			associated.box.SetPos(destination);
			destination = PenguinBody::player->GetCenter();
			Vec2 target;

			Minion * shooter;
			int dcurr=-1, ind=0;
			for (int i=0;i<nMinions;i++){
				shooter = (Minion *)minionArray[i].lock()->GetComponent("Minion");
				if (dcurr> (shooter->Pos()-destination).Abs() || dcurr==-1) {
					dcurr = (shooter->Pos()-destination).Abs();
					ind = i;
				}
			}
			shooter = (Minion *)minionArray[ind].lock()->GetComponent("Minion");

			target.x = destination.x - shooter->Pos().x;
			target.y = destination.y - shooter->Pos().y;


			shooter->Shoot(target);

			speed.x=0;
			speed.y=0;
			state=RESTING;
			restTimer.Restart();
		}
		else{
			associated.box.x = associated.box.x + (speed.x*dt);
			associated.box.y = associated.box.y + (speed.y*dt);
		}
	}
}

void Alien::Render(){

}

bool Alien::Is(std::string type){
	return type=="Alien";
}
Alien::~Alien(){
	alienCount--;
	minionArray.clear();
}

void Alien::NotifyCollision(GameObject& other){
	Bullet *bullet =(Bullet *) other.GetComponent("Bullet");
	if (bullet  != nullptr && !bullet->targetsPlayer){
		hp-=bullet->GetDamage();
		printf ("Alien: %d\n", hp);
		if (hp<=0){
			associated.RequestDelete();

			GameObject *explosionObject = new GameObject();
			Sprite * explosionSprite = new Sprite(*explosionObject , deathSpriteAddress, 4, 100, 0.4);
			explosionObject->AddComponent(explosionSprite);

			Sound *explosionSound = new Sound(explosionSoundAddress, *explosionObject);
			explosionObject->AddComponent(explosionSound);
			explosionSound->Play();

			explosionObject->box.x = associated.box.GetCenter().x - explosionObject->box.w/2 ;//+ Camera::GetInstance().pos.x;
			explosionObject->box.y = associated.box.GetCenter().y - explosionObject->box.h/2 ;//+ Camera::GetInstance().pos.y;


			Game::GetInstance().GetCurrentState().AddObject(explosionObject);
		}
	}

}


