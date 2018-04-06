#include "../include/GameObject.h"
#include "../include/Component.h"
#include "../include/Face.h"
#include "../include/Rect.h"
#include "../include/Sound.h"
#include "../include/Game.h"
#include "../include/State.h"
#include "../include/Sprite.h"
#include "../include/Music.h"
#include "../include/Vec2.h"



int main (int argc, char** argv){
	Game::GetInstance().Run();
	return 0;
}
