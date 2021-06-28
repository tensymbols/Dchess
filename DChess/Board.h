#pragma once
#include "gameObject.h"
#include <vector>
#include "piece.h"
class Board: public gameObject{
public:

	
	//Piece* GetBrdState(const int);
	//Board(const char*, Pos, SDL_Color wf, SDL_Color bf, int dim, int w, int h );
	using gameObject::Move;
	Board(const char*, Pos, SDL_Color wf, SDL_Color bf,int brd_dim ,int sqr_dim);
	~Board();
	void Init( char* fen);
	void Init();
	void Draw() override; // draws board and pieces
	void drawLegal();
	void unmarkLegal();
	
	void move(int pos1, int pos2, bool realBoard); // move function from one position to another (numbers)

	void mark(const int); // mark square with color
	void unmark(const int); // unmark square
	void keepInsde(Pos&); // keep piece inside while dragging when mouse position is out of board borders on screen
	
	void handleEvent(SDL_Event&); // handles events like mouse etc 

	void nextTurn();

	void allPseudoLegal(Piece*, bool realBoard);
	void potentialChecks(Piece* p);

	void processCheck(bool side);

	Pos getAbsPosition(int pos); // get absolute position of the piece (screen coords)
	int getPosFromMouse(Pos);


	Pos getCoordFromNumber(const int pos);
	int getNumberFromCoord(Pos);

	int getTypeFromLetter(const char c);
	
	void changeColor(SDL_Color, SDL_Color);
	

private:
	bool sideToMove=1;// 0 - black, 1 - white
	int semiClock=0;
	int fullClock=0;
	int sqr_dim=0;
	int brd_dim=8;

	std::vector<int> b_check;
	std::vector<int> w_check;

//////////////
	
		int prevMarked = 0;
		bool legalDrawn = 0;
		bool LMB_STATE = 0;
		bool initialized=0;
//////////////

	char _fen[256];

	void legal(std::vector<Pos>& deltas, Piece *, int depth, int typeOfCheck, bool);


	Piece* holdPiece=NULL;
	std::vector<int> temp_moves;
	bool* marked;
	SDL_Color* colSquares=NULL;
	SDL_Rect* squares=NULL;

	SDL_Color bfield;
	SDL_Color wfield;
	std::vector<Piece*> pieces_; 
	std::vector<Piece*> tempPieces_;
	Piece** BoardState=NULL;
	Piece** tempBoard = NULL;// contains "references" to pieces, refers to NULL when cell is not occupied*/
	Piece* bKing = NULL; Piece* wKing = NULL;
};


