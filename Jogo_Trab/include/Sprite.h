#ifdef SPRITE_CLASS
#else
#define SPRITE_CLASS

#include "SDL2/SDL.h"


class Sprite: public Component {
	public:
		Sprite();
		Sprite(std::string type);
		~Sprite();
		void Open (std::string type);
		void SetClip (int x, int y, int w, int h);
		void Render (int x, int y);
		int GetWidth ();
		int GetHeight();
		bool IsOpen();
		bool Is (std::string type);

	private:
		SDL_Texture * texture;
		int width;
		int height;
		SDL_Rect * clipRect;
};
#endif
