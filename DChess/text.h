#include <vector>
#include "gameObject.h"
#include <iostream>
#include <string>

class text : public gameObject {
public:
	text(Pos pos, SDL_Color cl, TTF_Font* font, std::string str);
	text(Pos pos, SDL_Color cl, TTF_Font* font, const char* str);
	//~text();
private:
	const char* text_ = NULL;
	TTF_Font* font_ = NULL;
};