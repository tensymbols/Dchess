#pragma once
#include "SDL.h"
#include "SDL_image.h"

#include "texmng.h"
#include "gameObject.h"
//#include "Board.h"


class game {

public:
	game();
	~game();

	void init(const char* title, const int xpos, const int ypos, const int width, const int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running();
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;


	int cnt = 0;

};