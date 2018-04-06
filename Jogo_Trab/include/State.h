#ifdef STATE_CLASS
#else
#define STATE_CLASS

#include <memory>
#include "SDL2/SDL.h"
#include "Sprite.h"
#include "Music.h"
#include <vector>

#include <iostream>




class State{
	public:
		State();
		void AddObject(int MouseX, int MouseY);
		void Input();
		bool QuitRequested();
		void LoadAssets();
		void Update(float dt);
		void Render();
		std::vector <std::unique_ptr<GameObject>> objectArray;
	private:
		~State();
		Sprite *bg;
		Music *music;
		bool quitRequested;
};


#endif
