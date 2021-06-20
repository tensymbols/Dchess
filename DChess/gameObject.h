#pragma once
#include "SDL.h"
#include "pos.h"
#include "graphics.h"
class gameObject {

public:
	gameObject(const char* , Pos, int w,int h);
	gameObject(const char*, Pos);
	virtual void Move(Pos);
	virtual void update();
	virtual void Draw();
	virtual void Draw(Pos pos);
	void setPos(Pos pos);
	SDL_Renderer* getRnd() { return rnd; }
	Pos getPos() { return pos_; }
	int getW() const;
	int getH() const;
	bool isInside(Pos);
	static SDL_Renderer* rnd;
	static graphics *gfx;
private:

	SDL_Texture* texture_ = NULL;
	
	Pos pos_;
	int width;
	int height;
};