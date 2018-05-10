#include "../include/Alien.h"
#include "../include/Sprite.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"
#include "../include/Minion.h"
#include "../include/State.h"
#include "../include/Game.h"

#define W 0.001
const float V = 0.5; // Constante proporcional à velocidade base do Alien


/* TODO:
 *	implementar coisas do final do roteiro
 */









const std::string alienSpriteAdd	= 	"assets/img/alien.png";

Alien::Action::Action(ActionType type, float x, float y){
	pos.x=x;
	pos.y=y;
	this->type=type;
}

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



}

void Alien::Start(){
	for (int i=0; i<nMinions; i++){
			GameObject *minionObject = new GameObject();
			Minion *minion = new Minion(*minionObject, Game::GetInstance().GetState().GetObjectPtr(&associated), (float)(i*2*PI/(nMinions)));
			minionObject->AddComponent(minion);
			minionArray.push_back(Game::GetInstance().GetState().AddObject(minionObject));
		}
}

void Alien::Update(float dt){
	associated.angle += 180*W*dt/PI;

	if (InputManager::GetInstance().IsMouseDown(SDL_BUTTON_LEFT)){
		Action *action = new Action(Action::SHOOT,InputManager::GetInstance().GetMouseX() + Camera::GetInstance().pos.x,InputManager::GetInstance().GetMouseY() + Camera::GetInstance().pos.y);
		taskQueue.push(*action);


	}
	if (InputManager::GetInstance().MousePress(SDL_BUTTON_RIGHT)){
		Action *action = new Action(Action::MOVE, -associated.box.w/2 + InputManager::GetInstance().GetMouseX() + Camera::GetInstance().pos.x, -associated.box.h/2 + InputManager::GetInstance().GetMouseY() + Camera::GetInstance().pos.y);
		taskQueue.push(*action);
	}


	if (!taskQueue.empty()){
		Action action = taskQueue.front();
		if (action.type==Action::MOVE){
			if (speed.x==0 && speed.y==0) speed = (action.pos - associated.box.Pos()).Uni()*V;

			if ( (action.pos - associated.box.Pos()).Abs()<= V*dt){
				associated.box.SetPos(action.pos);
				taskQueue.pop();
				speed.x=0;
				speed.y=0;
			}
			else{
				printf ("	%g Action box: X=%f y=%f\n",dt, action.pos.x, action.pos.y);
				printf ("Associated box	: X=%f Y=%f\n", associated.box.x, associated.box.y);
				printf ("Speed		: X=%f Y=%f\n", speed.x, speed.y);
				associated.box.x = associated.box.x + (speed.x*dt);
				associated.box.y = associated.box.y + (speed.y*dt);
			}
		}

		else if (action.type==Action::SHOOT){

			Vec2 target;

			Minion * shooter;
			int dcurr=-1, ind=0;
			for (int i=0;i<nMinions;i++){
				shooter = (Minion *)minionArray[i].lock()->GetComponent("Minion");
				if (dcurr> (shooter->Pos()-action.pos).Abs() || dcurr==-1) {
					dcurr = (shooter->Pos()-action.pos).Abs();
					ind = i;
				}
				}
			shooter = (Minion *)minionArray[ind].lock()->GetComponent("Minion");

			target.x = action.pos.x - shooter->Pos().x;
			target.y = action.pos.y- shooter->Pos().y;


			shooter->Shoot(target);
			taskQueue.pop();
		}

	if (hp<=0){
		associated.RequestDelete();
	}

	}
}

void Alien::Render(){

}

bool Alien::Is(std::string type){
	return type=="Alien";
}
Alien::~Alien(){
	minionArray.clear();
}


