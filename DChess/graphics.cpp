#include "graphics.h"

void graphics::DrawRect(SDL_Surface* surf, int x, int y, int dim_x, int dim_y, SDL_Color cl)
{
	/*	void *ptr = surf->pixels;
		for (size_t i = x; i < dim_x; i++)
		{
			for (size_t j = x; j < dim_y; j++)
			{

			}
		}
		*/
}

void graphics::DrawRect(SDL_Color cl, SDL_Rect rect)
{
	SDL_SetRenderDrawColor(renderer, cl.r, cl.g, cl.b, 255);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderDrawRect(renderer, &rect);
}