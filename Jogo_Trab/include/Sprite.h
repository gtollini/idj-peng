#ifdef SPRITE_CLASS
#else
#define SPRITE_CLASS

#include "SDL2/SDL.h"


class Sprite {
	public:
		Sprite();
		Sprite(char * file);
		~Sprite();
		void Open (char * file);
		void SetClip (int x, int y, int w, int h);
		void Render (int x, int y);
		int GetWidth ();
		int GetHeight();
		bool IsOpen();
	private:
		SDL_Texture * texture;
		int width;
		int height;
		SDL_Rect * clipRect;
};
#endif
