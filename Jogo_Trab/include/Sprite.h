#ifdef SPRITE_CLASS
#else
#define SPRITE_CLASS
#include "Component.h"
#include "SDL2/SDL.h"
#include "Timer.h"


class Sprite: public Component {
	public:
		Sprite(std::string file);
		Sprite(GameObject& associated);
		Sprite(std::string type, GameObject& associated);
		Sprite(int x, int y,std::string type, GameObject& associated);
		Sprite(GameObject& associated, std::string file, int frameCount=1, float frameTime=1, float secondsToSelfDestruct = 0);
		~Sprite();

		void Open (std::string type);
		void SetClip (int x, int y, int w, int h);
		void SetFrame (int frame);
		void SetFrameTime(float frameTime);
		void SetFrameCount (int frameCount);
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
		Timer selfDestructCount;
		float secondsToSelfDestruct;

		int frameCount;
		int currentFrame;
		float timeElapsed;
		float frameTime;
		SDL_Texture * texture;
		int width;
		int height;
		SDL_Rect clipRect;
		Vec2 scale;

};
#endif
