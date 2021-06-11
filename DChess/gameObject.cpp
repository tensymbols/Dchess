#include "gameObject.h"
#include "texmng.h"

gameObject::gameObject(const char* texfile, SDL_Renderer* rnd, Pos pos, int w, int h) : pos_(pos), rnd(rnd), width(w), height(h)
{
	texture_ = texLoader::loadTexture(texfile, rnd);
}
gameObject::gameObject(const char* texfile, SDL_Renderer* rnd, Pos pos) : pos_(pos), rnd(rnd)
{
	texture_ = texLoader::loadTexture(texfile, rnd);
}

void gameObject::update() {

}

void gameObject::Draw()
{
	SDL_Rect temp{pos_.x, pos_.y,width, height };
	SDL_RenderCopy(rnd, texture_, &temp, &temp);
}
