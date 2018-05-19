#include "../include/Component.h"
#include "../include/GameObject.h"
#include "../include/Face.h"
#include "../include/Rect.h"
#include "../include/Sound.h"
#include "../include/Game.h"
#include "../include/Sprite.h"
#include "../include/Music.h"
#include "../include/StageState.h"
#include "../include/Vec2.h"
#include "../include/Resources.h"
#include "../include/TitleState.h"



int main (int argc, char** argv){
	TitleState *titleState = new TitleState();
	Game::GetInstance().Push(titleState);

//	StageState *stageState = new StageState();
//	Game::GetInstance().Push(stageState);

	Game::GetInstance().Run();
	Resources::GetInstance().ClearAll();
	return 0;
}
