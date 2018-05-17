#ifndef CLASS_ALIEN
#define CLASS_ALIEN
#include "Component.h"
#include <queue>
#include "Vec2.h"
#include "Timer.h"

class Alien : public Component {
public:
	Alien(GameObject& Associated, int nMinions);
	~Alien();
	void Start();
	void Update(float dt);
	void Render();
	bool Is(std::string type);

	void NotifyCollision(GameObject& other);
private:
	int alienCount;

	enum AlienState { MOVING, RESTING};
	AlienState state;
	Timer restTimer;
	Vec2 destination;

	Vec2 speed;
	int hp, nMinions;
	std::vector<std::weak_ptr<GameObject>> minionArray;
};




#endif
