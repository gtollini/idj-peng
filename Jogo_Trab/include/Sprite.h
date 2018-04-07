#ifdef SPRITE_CLASS
#else
#define SPRITE_CLASS
#include "Component.h"
#include "SDL2/SDL.h"


class Sprite: public Component {
	public:
		Sprite(GameObject& associated);
		Sprite(std::string type, GameObject& associated);
		Sprite(int x, int y,std::string type, GameObject& associated);
		~Sprite();
		void Open (std::string type);
		void SetClip (int x, int y, int w, int h);
		void Render ();
		void Update(float dt);
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
