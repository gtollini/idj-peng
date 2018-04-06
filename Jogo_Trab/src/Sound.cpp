#include "../include/Sound.h"
#include "SDL2/SDL_mixer.h"

Sound::Sound(GameObject& associated){
	Sound::associated=associated;
	chunk=nullptr;
	channel=0;
}

Sound::Sound(GameObject& associated, std::string file){
	Sound(GameObject& associated);
	Open(file);
}

void Sound::Play(int times=1){
	channel = Mix_PlayChannel (-1, chunk, times-1);
}

void Sound::Stop(){
	Mix_HaltChannel (channel);
}

void Sound::Open(std::string file){
	chunk = Mix_LoadWAV(file.c_str());
}

Sound::~Sound(){
	if (chunk!=nullptr) Mix_HaltChannel (channel);
	Mix_FreeChunk(chunk);
}
