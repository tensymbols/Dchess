#pragma once
#include "SDL.h"
#include "texmng.h"
#include "pos.h"

class gameObject {

public:
	gameObject(const char* , SDL_Renderer*, Pos);
	virtual void update();
	virtual void Draw() = 0;
	SDL_Renderer* getRnd() { return rnd; }
	Pos getPos() { return pos_; }
private:

	SDL_Texture* texture_;
	SDL_Renderer* rnd;
	Pos pos_;

};