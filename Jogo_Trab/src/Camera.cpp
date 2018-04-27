#include "../include/Camera.h"
#include "../include/GameObject.h"
#include "../include/InputManager.h"
#include "../include/Vec2.h"

#define CAMSHOW 0

/*Camera& Camera::GetInstance(){
	static Camera camera;
	return camera;
}*/


void Camera::Follow(GameObject* newFocus){
	focus=newFocus;
}

void Camera::Unfollow(){
	focus=nullptr;
}

void Camera::Update(float dt){
	if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)) if (speed.x>-5) speed.x--;
	if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)) if (speed.x<5)speed.x++;
	if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)) if (speed.y>-5) speed.y--;
	if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)) if (speed.y<5)speed.y++;

	if (!InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY) && !InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)) speed.x=0;
	if (!InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY) && !InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)) speed.y=0;

	pos=pos+speed*(dt/500);
	if (CAMSHOW) printf("%g\n", dt);
	if (CAMSHOW) printf("Pos	-	X:%f Y:%f\n", pos.x, pos.y);
	if (CAMSHOW) printf("Speed	-	X:%f Y:%f\n", speed.x, speed.y);
}

