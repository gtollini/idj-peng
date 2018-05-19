#ifndef INCLUDE_TEXT_H_
#define INCLUDE_TEXT_H_



#include "Component.h"
#include "GameObject.h"
#include <SDL2/SDL_ttf.h>
#include "Timer.h"


class Text: public Component{
public:
	enum TextStyle {SOLID, SHADED, BLENDED};

	Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color);
	~Text();

	void Update(float dt);
	void Render();
	bool Is(std::string type);

	void SetText(std::string text);
	void SetColor(SDL_Color color);
	void SetStyle(TextStyle style);
	void SetFontFile(std::string fontFile);
	void SetFontSize(int fontSize);
private:
	Timer timer;
	float h,w;
	void RemakeTexture();

	TTF_Font* font;
	SDL_Texture* texture;

	std::string text;
	TextStyle style;
	std::string fontFile;
	int fontSize;
	SDL_Color color;
};




#endif
