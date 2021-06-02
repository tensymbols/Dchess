#include <iostream>
#include "game.h"
int main(int argc, char* argv[]) {

	
	game Game;

	Uint32 timefromstart;
	const int fps = 120;
	int msPerFrame = 1000 / fps;

	Game.init("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800,600,0);
	
	while (Game.running()) {
		timefromstart = SDL_GetTicks();
		Uint32 temp;
		int timePerFrame;
		Game.handleEvents();
		Game.update();
		Game.render();

		temp = SDL_GetTicks();

		timePerFrame = temp - timefromstart;

		std::cout << timePerFrame << std::endl;
		if (timePerFrame < msPerFrame) {
			SDL_Delay(msPerFrame - timePerFrame);
		}


	}
	Game.clean();
	
	
	return 0;
}