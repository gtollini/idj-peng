#include "../include/Sound.h"
#include "SDL2/SDL_mixer.h"
#include "../include/Resources.h"

Sound::Sound(GameObject& associated) : Component(associated){
	chunk=nullptr;
	channel=0;
}

Sound::Sound(std::string file, GameObject& associated) : Component(associated){
	chunk=nullptr;
	channel=0;
	Open(file);
}

void Sound::Play(int times){
	channel = Mix_PlayChannel (-1, chunk, times-1);
}

void Sound::Stop(){
	Mix_HaltChannel (channel);
}

void Sound::Update(float dt){

}

void Sound::Render(){

}

void Sound::Open(std::string file){
	chunk = Resources::GetInstance().GetSound(file);
}

bool Sound::Is(std::string type){
	return type=="Sound";
}


Sound::~Sound(){
	if (chunk!=nullptr) Mix_HaltChannel (channel);
	chunk=nullptr;
	Resources::GetInstance().ClearSounds();
}
