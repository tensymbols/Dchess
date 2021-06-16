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

		brd = new Board("textures/pieces0.png", {128,128 }, { 99, 65, 34,255 }, { 255, 221, 191, 255 }, 64);
		//const char fen[] = { "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR " };
		const char fen[] = { "8/8/8/8/RrBbQqq " };
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
	/*std::string pos;
	cnt++;
	try{
		std::cin >> pos;
		const char* p = pos.c_str();
		brd->Move(p);
	}
	catch (std::string s) {
		std::cout << s << "\n";
		getchar();
	}*/
	
}

void game::render()
{
	SDL_RenderClear(renderer);
	
	/*for (size_t i = 0; i < 12; i++)
	{
		SDL_RenderCopy(renderer, piecesTex, &pieceTexRekts[i], &piecePosRekts[i]);
	}*/

	//SDL_RenderCopy(renderer, piecesTex, &pieceRekts[i], &dstRekt);
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


