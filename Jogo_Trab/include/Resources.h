#ifndef RESOURCES_CLASS
#define RESOURCES_CLASS

#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include <iostream>
#include <unordered_map>


class Resources {
public:
	SDL_Texture* GetImage(std::string file);
	void ClearImages();

	Mix_Music* GetMusic(std::string file);
	void ClearMusics();

	Mix_Chunk * GetSound(std::string file);
	void ClearSounds();

    TTF_Font* GetFont(std::string file, int size);
    void ClearFonts();

    void ClearAll();

	static Resources& GetInstance();

private:
	std::unordered_map<std::string, SDL_Texture*> 	imageTable;
	std::unordered_map<std::string, Mix_Music*> 	musicTable;
	std::unordered_map<std::string, Mix_Chunk*> 	soundTable;
	std::unordered_map<std::string, TTF_Font*> 		fontTable;
};





#endif
