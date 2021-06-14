#include <iostream>
#include "game.h"

#define _CRT_SECURE_NO_WARNINGS
int main(int argc, char* argv[]) {

	
	game Game;

	Uint32 timefromstart;
	const int fps = 120;
	int msPerFrame = 1000 / fps;

	Game.init("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 768,768,0);
	
	while (Game.running()) {
		timefromstart = SDL_GetTicks();
		Uint32 temp;
		int timePerFrame;
		Game.render();
		Game.handleEvents();
		Game.update();
		

		temp = SDL_GetTicks();

		timePerFrame = temp - timefromstart;

	//	std::cout << timePerFrame << std::endl;
		if (timePerFrame < msPerFrame) {
			SDL_Delay(msPerFrame - timePerFrame);
		}


	}
	Game.clean();
	
	
	return 0;
}