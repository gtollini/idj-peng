#include "../include/Text.h"
#include "../include/Game.h"
#include "../include/Camera.h"


#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>


Text::Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color) :
	Component (associated), fontFile(fontFile), fontSize(fontSize), style(style), text(text), color(color), texture(nullptr){
	RemakeTexture();
	timer.Restart();
	h=associated.box.h;
	w=associated.box.w;
}

Text::~Text() {
    if(texture!=nullptr){
        SDL_DestroyTexture(texture);
    }
}

void Text::Update(float dt){
	timer.Update(dt);
	associated.box.h= (timer.Get()>250)? 0 : h;
	associated.box.w= (timer.Get()>250)? 0 : w;

	if (timer.Get()>500) timer.Restart();
}

void Text::Render(){
	SDL_Rect dstRect{}, clipRect;
	dstRect.x = (int) (associated.box.x - Camera::GetInstance().pos.x);
	dstRect.y = (int) (associated.box.y - Camera::GetInstance().pos.y);
	dstRect.w = (int) (associated.box.w);
	dstRect.h = (int) (associated.box.h);

	clipRect.x = 0;
	clipRect.y = 0;
	clipRect.w = (int) (associated.box.w);
	clipRect.h = (int) (associated.box.h);

	if(SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, associated.angle, nullptr, SDL_FLIP_NONE) != 0){
		printf ("Erro ao renderizar texto\n");
	}
}

bool Text::Is(std::string type){
	return type == "Text";
}

void Text::SetText(std::string text){
    this->text = text;
    RemakeTexture();
}

void Text::SetColor(SDL_Color color){
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(Text::TextStyle style){
    this->style = style;
    RemakeTexture();
}

void Text::SetFontFile(std::string fontFile){
    this->fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize(int fontSize){
    this->fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture(){
	if(texture!=nullptr){
		SDL_DestroyTexture(texture);
	}

	font = Resources::GetInstance().GetFont(fontFile, fontSize);
	if (font==nullptr){
		printf ("Erro ao carregar fonte\n");
	}
	SDL_Surface * aux;
	if 		(style == SOLID){
		aux = TTF_RenderText_Solid(font, text.c_str(), color);
	}
	else if (style == SHADED){
		aux = TTF_RenderText_Shaded(font, text.c_str(), color, (SDL_Color){0, 0, 0, 0});
	}
	else if (style == BLENDED){
		aux = TTF_RenderText_Blended(font, text.c_str(), color);
	}
	texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), aux);
	if (texture == nullptr){
		printf ("Falha ao converter superficie em textura\n");
	}

	associated.box.w = aux->w;
	associated.box.h = aux->h;

	SDL_FreeSurface(aux);
}
