#include "game.h"

#include "Board.h"
#include "texmng.h"
#include <iostream>

SDL_Renderer* gameObject::rnd = nullptr;
SDL_Renderer* graphics::renderer = nullptr;
graphics* gameObject::gfx = nullptr;
graphics* gfx;
Board* brd;


game::game() :isRunning(false)
{}

game::~game() {}



void game::init(const char* title, const int xpos, const int ypos, const int width, const int height, bool fullscreen) {

	int flags = 0;

	if (fullscreen) { flags = SDL_WINDOW_FULLSCREEN; }
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
	//	std::cout << "INITIALIZED succesfully" << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			

		}
		
		gameObject::rnd = renderer;
		graphics::renderer = renderer;
		gameObject::gfx = gfx;

		brd = new Board("textures/pieces0.png", {64,64 }, { 129, 164, 109,255 }, { 249, 253, 235, 255 }, 10, 64);
		const char fen[] = { "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR " };
		//const char fen[] = { "nnnnn/NNNNNN " };
		//const char fen[] = { "qqqqqqqqqq/5555555555/QQQQQQQQQQ " };
		brd->Init(fen);
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
		case SDL_MOUSEMOTION:
			brd->handleEvent(event);
		//	else brd->unmark(brd->getPosFromMouse(mpos));
			
		//	std::cout << event.motion.x << " " << event.motion.y << "\n";
		
			break;
		case SDL_MOUSEBUTTONDOWN:
			brd->handleEvent(event);
			break;
		case SDL_MOUSEBUTTONUP:
			brd->handleEvent(event);
			break;
		default:
			break;
	}
}

void game::update()
{

}

void game::render()
{
	SDL_RenderClear(renderer);

	brd->Draw();
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderPresent(renderer);
	

}

void game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);


	SDL_Quit();
//	std::cout << "CLEANED" << std::endl;
}

bool game::running()
{
	return isRunning;
}


