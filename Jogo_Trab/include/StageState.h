#ifdef STATE_CLASS
#else
#define STATE_CLASS

#include <memory>
#include "SDL2/SDL.h"
#include "Sprite.h"
#include "Music.h"
#include <vector>
#include <iostream>
#include "Resources.h"
#include "Camera.h"
#include "TileSet.h"
#include "State.h"




class StageState : public State{
	public:
		StageState();
		~StageState();

		void LoadAssets();
		void Update(float dt);
		void Render();

		void Start();
		void Pause();
		void Resume();

	private:
		TileSet* tileSet;
		Music *backgroundMusic;
};


#endif
