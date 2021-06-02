#pragma once
#include "SDL.h"
#include "SDL_image.h"


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

	void pieceInit();
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

	

	SDL_Texture* piecesTex;

	SDL_Rect dstRekt;
	SDL_Rect pieceTexRekts[12];
	SDL_Rect piecePosRekts[12];

	int cnt = 0;

};