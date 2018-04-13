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




class State{
	public:
		State();
		void AddObject(int MouseX, int MouseY);
		void Input();
		bool QuitRequested();
		void LoadAssets();
		void Update(float dt);
		void Render();
		void Delete();

	private:
		~State();
		Music *music;
		bool quitRequested;
		std::vector<std::unique_ptr<GameObject>> objectArray;

};


#endif
