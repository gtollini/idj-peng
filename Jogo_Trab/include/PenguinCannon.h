#ifndef CLASS_PENGUINCANNON
#define CLASS_PENGUINCANNON
#include "Component.h"
#include "Timer.h"

class PenguinCannon: public Component{
public:
	PenguinCannon(GameObject& associated, std::weak_ptr< GameObject > penguinBody);

	void Start();
	void Update(float dt);
	void Render();
	bool Is(std::string type);

	void NotifyCollision(GameObject& other);

	void Shoot();
private:
	Timer time;
	std::weak_ptr<GameObject> pbody;
	float angle;

};


#endif
