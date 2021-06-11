#pragma once
#include "SDL.h"
#include "pos.h"

class gameObject {

public:
	gameObject(const char* , SDL_Renderer*, Pos, int w,int h);
	gameObject(const char*, SDL_Renderer*, Pos);
	virtual void update();
	virtual void Draw();
	virtual void Draw(Pos pos);
	SDL_Renderer* getRnd() { return rnd; }
	Pos getPos() { return pos_; }
private:

	SDL_Texture* texture_;
	SDL_Renderer* rnd;
	Pos pos_;
	int width;
	int height;
};