#ifdef SPRITE_CLASS
#else
#define SPRITE_CLASS
#include "Component.h"
#include "SDL2/SDL.h"
#include "Resources.h"


class Sprite: public Component {
	public:
		Sprite(std::string file);
		Sprite(GameObject& associated);
		Sprite(std::string type, GameObject& associated);
		Sprite(std::string type, GameObject& associated, Resources* resources);
		Sprite(int x, int y,std::string type, GameObject& associated);
		Sprite(int x, int y,std::string type, GameObject& associated, Resources* resources);
		~Sprite();

		void Open (std::string type);
		void SetClip (int x, int y, int w, int h);
		void Render ();
		void Render(int srcX, int srcY, int h, int  w,  int dstX, int dstY);
		void Update(float dt);
		void Render (int x, int y);

		void SetScale(float ScaleX, float ScaleY);

		Vec2 GetScale();
		int GetWidth ();
		int GetHeight();
		bool IsOpen();
		bool Is (std::string type);

		void Center();

	private:
		SDL_Texture * texture;
		int width;
		int height;
		SDL_Rect clipRect;
		Resources resources;
		Vec2 scale;

};
#endif
