#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "../include/Game.h"
#include "../include/InputManager.h"
#include "../include/StageState.h"


#define LOOP_MENU 0
Game *Game::instance;

Game::Game(char * title, int width, int height){
	instance=this;
	dt=0;
	frameStart=0;
	if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)){
		printf ("erro na inicialização do SDL\n");

		abort();
	}
	if (!IMG_Init (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)){
		printf ("erro na inicialização da imagem\n");

		SDL_Quit();
		abort();
	}
	if (!(Mix_Init (MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MOD | MIX_INIT_FLUIDSYNTH | MIX_INIT_MODPLUG))
		|| (Mix_OpenAudio (MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024))){
		printf ("Erro na inicialização do áudio\n");

		IMG_Quit();
		SDL_Quit();
		abort();
	}

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,  0);
	if (window==nullptr){
		printf ("Erro na inicialização da janela\n");

		Mix_CloseAudio();
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
		abort();
	}
	renderer = SDL_CreateRenderer ( window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer==nullptr){
		printf ("Erro na inicialização do renderizador\n");

		SDL_DestroyWindow(window);
		Mix_CloseAudio();
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
		abort();
	}
	if (TTF_Init()){
		printf ("Erro na inicialização das fontes\n");

		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		Mix_CloseAudio();
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
		abort();
	}
	this->storedState = nullptr;
}

Game::~Game(){
	if (storedState!=nullptr) delete storedState;

	while (!stateStack.empty()){
		stateStack.pop();
	}

	Resources::GetInstance().ClearAll();

	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	abort();
}

Game& Game::GetInstance () {
	char nome[40] = "Gabriel de Carvalho Tollini, 140020454";
	if (instance  ==  nullptr) instance = new Game(nome, 1024, 600);
	return *instance;
	}

State& Game::GetCurrentState(){
	return *stateStack.top();
}

SDL_Renderer* Game::GetRenderer(){
	return renderer;
}

void Game::Push(State* state){
	storedState = state;
}

void Game::Run(){
	if (storedState==nullptr){
		printf ("ERRO: não foi possível carregar o estado inicial do jogo. Encerrando...\n");
		return;
	}

	stateStack.emplace(storedState);
	stateStack.top()->Start();
	storedState=nullptr;

	while (!stateStack.empty() && !stateStack.top()->QuitRequested()){

		if (stateStack.top()->PopRequested()){
			stateStack.top()->Pause();
			stateStack.pop();
			Resources::GetInstance().ClearAll();
			Camera::GetInstance().pos.x=0;
			Camera::GetInstance().pos.y=0;
			if (!stateStack.empty()) stateStack.top()->Resume();
		}
		if (storedState!=nullptr){
			if (!stateStack.empty()) stateStack.top()->Pause();
			stateStack.emplace(storedState);
			stateStack.top()->Start();
			storedState=nullptr;
		}


		if (LOOP_MENU) printf (" 		Calculating dt\n");
		CalculateDeltaTime();
		if (LOOP_MENU)printf (" 		Updating input\n");
		InputManager::GetInstance().Update();
		if (LOOP_MENU)printf (" 		Updating state\n");
		stateStack.top()->Update(dt);
		if (LOOP_MENU)printf (" 		Rendering state\n");
		stateStack.top()->Render();
		if (LOOP_MENU)printf (" 		Rendering\n");
		SDL_RenderPresent(renderer);
		if (LOOP_MENU)printf (" 		Done! dt\n");
		SDL_Delay(33);}
	Resources::GetInstance().ClearAll();

}

void Game::CalculateDeltaTime(){
	int old=frameStart;
	frameStart=SDL_GetTicks ();
	dt = (frameStart-old);

}

float Game::GetDeltaTime(){
	return dt;
}
