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
	void Init(const char* fen);
	void Draw() override; // draws board and pieces
	void drawLegal();
	void unmarkLegal();
	
	void move(int pos1, int pos2); // move function from one position to another (numbers)

	void mark(const int); // mark square with color
	void unmark(const int); // unmark square
	void keepInsde(Pos&); // keep piece inside while dragging when mouse position is out of board borders on screen
	
	void handleEvent(SDL_Event&); // handles events like mouse etc 



	std::vector<int> allLegal(Piece*);

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
//////////////
	bool b_check = false;
	bool w_check = false;
		int prevMarked = 0;
		bool legalDrawn = 0;
		bool LMB_STATE = 0;
//////////////

	std::vector<int> legal(std::vector<Pos>& deltas, int pos, int depth);
	bool isLegal(Piece*, int pos);

	Piece* holdPiece;
	std::vector<int> temp_moves;
	bool* marked;
	SDL_Color* colSquares;
	SDL_Rect* squares;

	SDL_Color bfield;
	SDL_Color wfield;
	std::vector<Piece*> pieces_; // contains ehm... uwu...  >w<
	Piece** BoardState; // contains "references" to pieces, refers to NULL when cell is not occupied*/
	
};


