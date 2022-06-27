#pragma once
#include "SDL.h"
#include "pos.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
class graphics {
public:

	void DrawRect(SDL_Surface*, int x, int y, int dim_x, int dim_y, SDL_Color);
	void DrawRect(SDL_Color cl, SDL_Rect rect);
	void DrawRect(SDL_Color cl, Pos pos, int w, int h);
	static SDL_Renderer* renderer;
private:

};