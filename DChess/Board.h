#pragma once
#include "gameObject.h"
#include <vector>
#include "piece.h"
class Board: public gameObject{
public:

	
	//Piece* GetBrdState(const int);
	//Board(const char*, Pos, SDL_Color wf, SDL_Color bf, int dim, int w, int h );
	Board(const char*, Pos, SDL_Color wf, SDL_Color bf, int dim);
	void Init(const char* fen);
	void Draw() override;
	void Show();
	using gameObject::Move;
	void Move(const char*);
	void Move(int pos1, int pos2);
	void mark(const int);
	void unmark(const int);
	void handleEvent(SDL_Event&);
	Pos getRelPosition(int pos);
	static int GetNumberPos(const char*);
	static const char* GetPosFromNumber(const int);
	static Pos GetCoordFromNumber(const int pos);
	static int getTypeFromLetter(const char c);
	void changeColor(SDL_Color, SDL_Color);
	int getPosFromMouse( Pos);

private:
	bool sideToMove;// 0 - black, 1 - white
	int semiClock;
	int fullClock;
	int dim;
	int prevMarked=0;
	Piece* holdPiece;
	bool marked[64];
	SDL_Color colSquares[64];
	SDL_Color bfield;
	SDL_Color wfield;
	std::vector<Piece*> pieces_; // contains ehm... uwu...  >w<
	Piece* BoardState[64]; // contains "references" to pieces, refers to NULL when cell is not occupied*/
	SDL_Rect squares[64];
};


