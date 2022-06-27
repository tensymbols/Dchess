#pragma once
#include "gameObject.h"
#include "Board.h"




class gInterface : public gameObject {

public:

	gInterface(Pos pos, int iDim, const char* tex, Board&);
	class iButton : public gameObject {

	public:
		iButton(int type, Pos pos, const char* tex, int w, int h);
		void restart(Board& brd);
		void mark() { marked = true; }
		void unmark() { marked = false; }
		bool isMarked() { return marked; }

	private:
		bool marked = 0;
		int type;

	};
	void handleEvent(SDL_Event& e);
	void Draw() override;
private:
	std::vector<iButton*> buttons;
	Board& brd;
	bool RMB_STATE = false;
	bool LMB_STATE = false;

	bool drag_ = false;
};