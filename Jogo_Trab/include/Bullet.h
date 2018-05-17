#ifndef BULLET_CLASS
#define BULLET_CLASS
#include "../include/Component.h"
#include "../include/GameObject.h"
#include "../include/Sprite.h"


class Bullet : public Component {
public:
	Bullet (GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount, float frameTime, bool targetsPlayer);
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	int GetDamage();

	void NotifyCollision(GameObject& other);

	bool targetsPlayer;
private:

	Vec2 speed;
	float distanceLeft;
	int damage;
};





#endif
