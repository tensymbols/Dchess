#pragma once
#include "SDL.h"
class Board {
public:
	Board(const int dim, SDL_Color w, SDL_Color b);
	void DrawBoard();

private:
	SDL_Color wSquares;
	SDL_Color bSquares;
	int dimension;
};