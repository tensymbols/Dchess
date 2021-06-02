#include "game.h"
#include "texmng.h"
#include <iostream>
#include "Board.h"
game::game() :isRunning(false)
{}

game::~game() {}



void game::init(const char* title, const int xpos, const int ypos, const int width, const int height, bool fullscreen) {

	int flags = 0;



	if (fullscreen) { flags = SDL_WINDOW_FULLSCREEN; }
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "INITIALIZED succesfully" << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			

		}

		piecesTex = texLoader::loadTexture( "textures/pieces0.png",renderer);
	

	
		pieceInit();



		isRunning = true;
		
	}

	
}

void game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type ) {
		case SDL_QUIT:
			isRunning = 0;
			break;
		default:
			break;
	}
}

void game::update()
{
	cnt++;
	piecePosRekts[0].x++;
}

void game::render()
{
	SDL_RenderClear(renderer);
	
	for (size_t i = 0; i < 12; i++)
	{
		SDL_RenderCopy(renderer, piecesTex, &pieceTexRekts[i], &piecePosRekts[i]);
	}

	//SDL_RenderCopy(renderer, piecesTex, &pieceRekts[i], &dstRekt);
	

	SDL_RenderPresent(renderer);
	

}

void game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);


	SDL_Quit();
	std::cout << "CLEANED" << std::endl;
}

bool game::running()
{
	return isRunning;
}

void game::pieceInit() {

	//texture init
	for (size_t i = 0; i < 12; i++)
	{
		pieceTexRekts[i].w = 64;
		pieceTexRekts[i].h = 64;
		pieceTexRekts[i].x = 64 * (i % 6);
		pieceTexRekts[i].y = 64 * (i / 6);
	}
	//position init
	for (size_t i = 0; i < 12; i++)
	{
		piecePosRekts[i].w = 64;
		piecePosRekts[i].h = 64;
		piecePosRekts[i].x = 64 * (i % 6);
		piecePosRekts[i].y = 64 * (i / 6);
	}
}
