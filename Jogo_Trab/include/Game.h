#ifdef GAME_CLASS
#else
#define GAME_CLASS

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "Sprite.h"
#include "State.h"
#include "Music.h"
#include "Resources.h"




class Game {
	public:
		~Game();
		void 			Run();
		SDL_Renderer* 	GetRenderer();
		State& 		 	GetState();
		static Game& 	GetInstance();

	private:
		static Game * instance;
		SDL_Window * window;
		SDL_Renderer * renderer;
		State * state;

		Game(char * title, int width, int height);
};

#endif
