#pragma once
#include "SDL.h"
#include "pos.h"
#include "graphics.h"
class gameObject {

public:
	gameObject(const char*, Pos, int w, int h);
	gameObject(const char*, Pos);
	~gameObject();
	void setTexture(SDL_Texture* tex);
	void setTexAlpha(int a);
	void setWidth(int);
	void setHeight(int);
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
	static graphics* gfx;
protected:

	SDL_Texture* texture_ = NULL;

	Pos pos_;
	int width_;
	int height_;
};/// remove gets and sets that could be implemented with protected