#include "GameObject.h"
#include "Vec2.h"
#ifndef CAMERA_CLASS
#define CAMERA_CLASS

class Camera{
public:
	static Camera& GetInstance();
	void Follow (GameObject* newFocus);
	void Unfollow();
	void Update(float dt);
	Vec2 pos;
	Vec2 speed;
private:
	GameObject* focus;
};





#endif
