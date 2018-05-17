#ifndef CLASS_COLLIDER
#define CLASS_COLLIDER

#include "Component.h"
#include "Vec2.h"

class Collider : public Component{
public:
	Collider(GameObject& associated, Vec2 scale = {1,1}, Vec2 offset = {0,0});
	Rect box;

	void Update(float dt);
	void Render();
	bool Is(std::string type);

	void SetScale(Vec2 scale);
	void SetOffset(Vec2 offset);
private:
	Vec2 scale, offset;

};


#endif
