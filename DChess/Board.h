#pragma once
#include "gameObject.h"
#include <vector>
#include "piece.h"
class Board: public gameObject{
public:

	
	//Piece* GetBrdState(const int);
	//Board(const char*, Pos, SDL_Color wf, SDL_Color bf, int dim, int w, int h );
	using gameObject::Move;
	Board(const char*, Pos, SDL_Color wf, SDL_Color bf, int dim);
	void Init(const char* fen);
	void Draw() override; // draws board and pieces
	void drawLegal();
	void Show(); // debug (deprecated xd)
	
	void Move(const char*);  // move function for text moves
	void Move(int pos1, int pos2); // move function from one position to another (numbers)

	void mark(const int); // mark square with color
	void unmark(const int); // unmark square
	void keepInsde(Pos&); // keep piece inside while dragging when mouse position is out of board borders on screen
	
	void handleEvent(SDL_Event&); // handles events like mouse etc 


	std::vector<int> allLegal(Piece*, int pos);

	Pos getAbsPosition(int pos); // get absolute position of the piece (screen coords)
	int getPosFromMouse(Pos);
	static int getNumberPos(const char*);
	static const char* getPosFromNumber(const int);
	static Pos getCoordFromNumber(const int pos);
	static int getTypeFromLetter(const char c);
	
	void changeColor(SDL_Color, SDL_Color);
	

private:
	bool sideToMove;// 0 - black, 1 - white
	int semiClock;
	int fullClock;
	int sqr_dim;
	int brd_dim=8;
	int prevMarked=0;
	std::vector<int> legal(Pos delta, int pos);
	bool isLegal(Piece*, int pos);
	Piece* holdPiece;
	std::vector<int> temp_moves;
	bool marked[64];
	SDL_Color colSquares[64];
	SDL_Color bfield;
	SDL_Color wfield;
	std::vector<Piece*> pieces_; // contains ehm... uwu...  >w<
	Piece* BoardState[64]; // contains "references" to pieces, refers to NULL when cell is not occupied*/
	SDL_Rect squares[64];
};


