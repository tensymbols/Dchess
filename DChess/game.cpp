#include "game.h"
#include "gInterface.h"
#include "Board.h"
#include "texmng.h"
#include <iostream>

SDL_Renderer* gameObject::rnd = nullptr;
SDL_Renderer* graphics::renderer = nullptr;
graphics* gameObject::gfx = nullptr;
graphics* gfx;
Board* brd;
gInterface* _interface;


game::game() :isRunning(false)
{}

game::~game() {}



void game::init(const char* title, const int xpos, const int ypos, const int width, const int height, bool fullscreen) {

	int flags = 0;
	int sqr_dim = 64;
	int brd_dim = 8;

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

		TTF_Init();

		brd = new Board("textures/pieces0.png", { 128,128 }, { 129, 164, 109,255 }, { 249, 253, 235, 255 }, brd_dim, sqr_dim);
		_interface = new gInterface({ 64,16 }, sqr_dim / 2, NULL, *brd);
		//char fen[] = { "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR " }; // 8x8 standard
		//char fen[] = { "5/6/rnbqkbnr/2/pppppppp/1/5/5/5/5/5/5/5/5/1/PPPPPPPP/2/RNBQKBNR " }; // 10x10 standard
		char fen[] = { "8/P/1/K/8/8/8/8/8/k/p " };

		brd->Init(fen);
		isRunning = true;

	}


}

void game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = 0;
		break;
	case SDL_MOUSEMOTION:
		brd->handleEvent(event);
		_interface->handleEvent(event);

		break;
	case SDL_MOUSEBUTTONDOWN:
		_interface->handleEvent(event);
		brd->handleEvent(event);


		break;
	case SDL_MOUSEBUTTONUP:
		brd->handleEvent(event);
		_interface->handleEvent(event);
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
	_interface->Draw();
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


