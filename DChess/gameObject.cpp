#include "gameObject.h"
#include "texmng.h"

gameObject::gameObject(const char* texfile,  Pos pos, int w, int h) : pos_(pos), width(w), height(h)
{
	if(texfile)	texture_ = texLoader::loadTexture(texfile, rnd);
}
gameObject::gameObject(const char* texfile, Pos pos) : pos_(pos)
{
	width = 0; height = 0;
	texture_ = texLoader::loadTexture(texfile, rnd);
}
void gameObject::Move(const Pos pos)
{
	pos_.x += pos.x;
	pos_.y += pos.y;
}

void gameObject::update() {

}

void gameObject::Draw()
{
	SDL_Rect temp{pos_.x, pos_.y,width, height };
	SDL_RenderCopy(rnd, texture_, NULL, &temp);
}
void gameObject::Draw(Pos pos)
{
	//SDL_Rect tex{ 0, pos.y,width, height };
	SDL_Rect temp{ pos.x, pos.y,width, height };
	SDL_RenderCopy(rnd, texture_, NULL, &temp);
}

void gameObject::setPos(Pos pos)
{
	pos_ = pos;
}



int gameObject::getW() const
{
	return width;
}
int gameObject::getH() const
{
	return height;
}


bool gameObject::isInside(Pos coord)
{
	return (coord.x>pos_.x && coord.x<pos_.x+width &&
			coord.y>pos_.y && coord.y < pos_.y + height);
}
