#pragma once
#include "SDL.h"
#include "SDL_image.h"
class graphics {
public:

	void DrawRect(SDL_Surface*,int x,int y, int dim_x, int dim_y, SDL_Color);
	void DrawRect(SDL_Color cl, SDL_Rect rect);
	static SDL_Renderer* renderer;
private:
	
};