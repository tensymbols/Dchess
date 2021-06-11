#include "gameObject.h"

gameObject::gameObject(const char* texfile, SDL_Renderer* rnd, Pos pos) : pos_(pos), rnd(rnd)
{
	texture_ = texLoader::loadTexture(texfile, rnd);
}

void gameObject::update() {

}
