#ifndef SOUND_CLASS
#define SOUND_CLASS
#include "Component.h"
#include "SDL2/SDL_mixer.h"
#include "GameObject.h"


class Sound : public Component {
	public:
		Sound(GameObject& associated);
		Sound(std::string file, GameObject& associated);
		~Sound();

		void Play (int times=1);
		void Stop();
		void Open(std::string file);
		bool IsOpen();

		void Update(float dt);
		void Render();
		bool Is(std::string type);
	private:
		Mix_Chunk* chunk;
		int channel;
};


#endif
