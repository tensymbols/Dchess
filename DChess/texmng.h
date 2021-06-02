#pragma once

#include "game.h"

class texLoader {
public:
	static SDL_Texture* loadTexture(const char* filename, SDL_Renderer* renderer);
private:
};