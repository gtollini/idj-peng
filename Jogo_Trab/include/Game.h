
#ifdef GAME_CLASS
#else
#define GAME_CLASS

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "Sprite.h"
#include "State.h"
#include "StageState.h"
#include "Music.h"
#include "Resources.h"

#include <stack>



class Game {
	public:
		Game(std::string title, int width, int height);
		~Game();

		static Game& 	GetInstance();
		SDL_Renderer* 	GetRenderer();
		State& 		 	GetCurrentState();

		void 			Push(State* state);

		void 			Run();

		float 			GetDeltaTime();

	private:
		void CalculateDeltaTime();

		int frameStart;
		float dt;

		static Game * instance;

		State * storedState;
		SDL_Window * window;
		SDL_Renderer * renderer;
		std::stack<std::unique_ptr<State>> stateStack;

		Game(char * title, int width, int height);
};

#endif
