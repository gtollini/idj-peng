#ifndef CLASS_MINION
#define CLASS_MINION
#include "Component.h"
#define PI 3.1415
class Minion : public Component{
public:
	Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg =0);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void Shoot (Vec2 target);
	Vec2 Pos();

	void NotifyCollision(GameObject& other);
private:
	std::weak_ptr<GameObject> alienCenter;
	float arc;

};


#endif
