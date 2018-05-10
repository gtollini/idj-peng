#ifndef CLASS_CAMERAFOLLOWER
#define CLASS_CAMERAFOLLOWER
#include "GameObject.h"
#include "Component.h"

class CameraFollower : public Component{
public:
	CameraFollower (GameObject& associated);
	void Update (float dt);
	void Render();
	bool Is(std::string type);
};




#endif
