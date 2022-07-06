#include "text.h"

text::text(Pos pos, SDL_Color cl, TTF_Font* font, std::string str) :
	font_(font), text_(str.c_str()), gameObject(NULL, pos)
{
	SDL_Surface* tSurface = TTF_RenderText_Solid(font, str.c_str(), cl);
	setTexture(SDL_CreateTextureFromSurface(rnd, tSurface));
	this->setWidth(tSurface->w);
	this->setHeight(tSurface->h);
	SDL_FreeSurface(tSurface);
}
text::text(Pos pos, SDL_Color cl, TTF_Font* font, const char* str) :
	font_(font), text_(str), gameObject(NULL, pos)
{
	SDL_Surface* tSurface = TTF_RenderText_Solid(font, str, cl);
	setTexture(SDL_CreateTextureFromSurface(rnd, tSurface));
	this->setWidth(tSurface->w);
	this->setHeight(tSurface->h);
	SDL_FreeSurface(tSurface);
}
/*text::~text() {
	delete text_;
	delete font_;
}*/
