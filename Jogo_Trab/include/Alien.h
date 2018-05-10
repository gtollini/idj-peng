#ifndef CLASS_ALIEN
#define CLASS_ALIEN
#include "Component.h"
#include <queue>
#include "Vec2.h"

class Alien : public Component {
public:
	Alien(GameObject& Associated, int nMinions);
	~Alien();
	void Start();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
private:
	class Action{
	public:
		enum ActionType { MOVE, SHOOT};
		Action(ActionType type, float x, float y);

		ActionType type;
		Vec2 pos;
	};

	Vec2 speed;
	int hp, nMinions;
	std::queue<Action> taskQueue;
	std::vector<std::weak_ptr<GameObject>> minionArray;
};




#endif
