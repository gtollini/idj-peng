#include "../include/Music.h"
#include "SDL2/SDL_mixer.h"
#include "../include/Resources.h"
#define STOPCONST 1000

Music::Music(){
	music=nullptr;
}
Music::Music(std::string file){
	Music();
	Open(file);
}

Music::~Music(){
	Stop(STOPCONST);
	Resources::GetInstance().ClearMusics();
}

void Music::Play(int i){
	Mix_PlayMusic (music, i);
}

void Music::Stop(int msToStop){
	Mix_FadeOutMusic (msToStop);
}

void Music::Open(std::string file){
	music = Resources::GetInstance().GetMusic(file);
}

bool Music::IsOpen(){
	return music!=nullptr;
}
