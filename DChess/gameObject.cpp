#include "gameObject.h"
#include "texmng.h"

gameObject::gameObject(const char* texfile, Pos pos, int w, int h) : pos_(pos), width_(w), height_(h)
{
	if (texfile)	texture_ = texLoader::loadTexture(texfile, rnd);
}
gameObject::gameObject(const char* texfile, Pos pos) : pos_(pos)
{
	width_ = 0; height_ = 0;
	if (texfile) texture_ = texLoader::loadTexture(texfile, rnd);
}
gameObject::~gameObject()
{
	if (texture_) { 
		SDL_DestroyTexture(texture_);
	}
}
void gameObject::setWidth(int w)
{
	width_ = w;
}
void gameObject::setHeight(int h)
{
	height_ = h;
}
/*gameObject::gameObject(SDL_Texture* tex, Pos pos) : pos_(pos), texture_(tex)
{
	width = 0; height = 0;
}*/
void gameObject::Move(const Pos pos)
{
	pos_.x += pos.x;
	pos_.y += pos.y;
}

void gameObject::setTexture(SDL_Texture* tex)
{
	texture_ = tex;
}

void gameObject::setTexAlpha(int a)
{
	SDL_SetTextureAlphaMod(texture_, a);
}

void gameObject::update() {

}

void gameObject::Draw()
{
	SDL_Rect temp{ pos_.x, pos_.y,width_, height_ };

	SDL_RenderCopy(rnd, texture_, NULL, &temp);
}
void gameObject::Draw(Pos pos)
{
	//SDL_Rect tex{ 0, pos.y,width, height };
	SDL_Rect temp{ pos.x, pos.y,width_, height_ };
	SDL_RenderCopy(rnd, texture_, NULL, &temp);
}

void gameObject::setPos(Pos pos)
{
	pos_ = pos;
}



int gameObject::getW() const
{
	return width_;
}
int gameObject::getH() const
{
	return height_;
}


bool gameObject::isInside(Pos coord)
{
	return (coord.x > pos_.x && coord.x<pos_.x + width_ &&
		coord.y>pos_.y && coord.y < pos_.y + height_);
}
