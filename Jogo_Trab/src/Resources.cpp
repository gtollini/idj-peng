#include "../include/Resources.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL.h"
#include "../include/Game.h"
#include "SDL2/SDL_mixer.h"

Resources& Resources::GetInstance(){
	static Resources res;
	return res;
}

SDL_Texture* Resources::GetImage(std::string file){
	std::unordered_map<std::string,SDL_Texture*>::const_iterator tuple;
	tuple = imageTable.find(file);
	if (tuple!=imageTable.end()) return tuple->second;

	SDL_Texture *texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(),file.c_str());
	if (texture==nullptr){
		printf ("Erro ao carregar textura em %s\n", file.c_str());
		return nullptr;
	}
	imageTable.emplace(file, texture);
	return texture;
}

void Resources::ClearImages(){
	imageTable.clear();
}

Mix_Music* Resources::GetMusic(std::string file){
	std::unordered_map<std::string,Mix_Music*>::const_iterator tuple;
	tuple = musicTable.find(file);
	if (tuple!=musicTable.end()) return tuple->second;
	Mix_Music *music =  Mix_LoadMUS (file.c_str());
	if (music == nullptr){
		printf ("Erro ao carregar música\n");
		return nullptr;
	}
	musicTable.emplace(file, music);
	return music;
}

void Resources::ClearMusics(){
	musicTable.clear();
}

Mix_Chunk* Resources::GetSound(std::string file){
	std::unordered_map<std::string,Mix_Chunk*>::const_iterator tuple;
	tuple = soundTable.find(file);
	if (tuple!=soundTable.end()) return tuple->second;
	Mix_Chunk *sound=  Mix_LoadWAV(file.c_str());
	if (sound == nullptr){
		printf ("Erro ao carregar música\n");
		return nullptr;
	}
	soundTable.emplace(file, sound);
	return sound;
}

void Resources::ClearSounds(){
	soundTable.clear();
}

void Resources::ClearAll(){
	ClearSounds();
	ClearMusics();
	ClearFonts();
	ClearImages();
}

TTF_Font* Resources::GetFont(std::string file, int size) {
	std::string id = file + std::to_string(size);
	std::unordered_map<std::string,TTF_Font*>::const_iterator tuple;
	tuple = fontTable.find(id);

    if(tuple != fontTable.end()){
        return tuple->second;
    }
    TTF_Font* font = TTF_OpenFont (file.c_str(), size);
    if(font == nullptr){
    	printf ("Erro ao carregar fonte \n");
        return nullptr;
    }
    fontTable.emplace(id, font);
    return font;
    }

void Resources::ClearFonts() {
    fontTable.clear();
}
