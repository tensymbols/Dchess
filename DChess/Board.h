#pragma once
#include "gameObject.h"
#include <vector>
#include "piece.h"
class Board: public gameObject{
public:

	
	//Piece* GetBrdState(const int);
	Board(const char*, SDL_Renderer*, Pos, SDL_Color wf, SDL_Color bf);
	void Init(const char* fen);
	void Draw() ;
	void Show();
	void Move(const char*);
	static int GetNumberPos(const char*);
	static const char* GetPosFromNumber(const int);
	static int getTypeFromLetter(const char c);
private:
	bool sideToMove;// 0 - black, 1 - white
	int semiClock;
	int fullClock;
	const int dim = 64;
	SDL_Color bfield;
	SDL_Color wfield;
	std::vector<Piece*> pieces_; // contains ehm... uwu...  ><
	Piece* BoardState[64]; // contains "references" to pieces, refers to NULL when cell is not occupied*/
	SDL_Rect squares[64];
};


