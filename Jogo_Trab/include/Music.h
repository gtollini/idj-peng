#ifdef MUSIC_CLASS
#else
#define MUSIC_CLASS
#include <iostream>
#include "SDL2/SDL_mixer.h"


class Music{
	public:
		Music();
		Music(std::string file);
		~Music ();
		void Stop (int msToStop);
		void Play (int times);
		void Open (std::string file);
		bool IsOpen ();

	private:
		Mix_Music * music;
};
#endif

